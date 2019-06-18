#include <iostream>
#include <queue>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <future>
#include <bot-types.h>

using namespace httplib;
using json = nlohmann::json;

class Bot {
    const chrono::milliseconds PollingFrequency = chrono::milliseconds(100);
    const chrono::milliseconds EngineFrequency = chrono::milliseconds(100);
    typedef struct {
        coord_t wheelSize;
        coord_t wheelDist;
        coord_t epsilon;
    } BotConfigType;

    Server svr;
    BotConfigType config;
    queue<BotTargetType> targets;
    std::atomic<int> numTargets;
    BotStatusType<atomic<coord_t>> status;
    std::future<void> engine;
    std::future<void> controller;

    void Engine() {
        while(1) {
            if (status.speed) {
                double tact = 1.0*EngineFrequency / chrono::seconds(1); 
                double distTact = 2.0*M_PI*config.wheelSize*status.speed * tact; 
                status.p.x += distTact*cos(status.theta);
                status.p.y += distTact*sin(status.theta);
            }
            this_thread::sleep_for(EngineFrequency);
        }

    }
    void Controller() {
        while(1) {
            if (numTargets.load(std::memory_order_relaxed)) {
                std::atomic_thread_fence(std::memory_order_acquire);
                volatile coord2d_t p = {status.p.x, status.p.y};

                if (status.speed == 0 && !targets.empty()) {
                    status.speed = targets.front().velocity;
                    status.theta = targets.front().p.x==p.x ? M_PI/2 :
                        atan((1.0*targets.front().p.y - p.y)/(targets.front().p.x-p.x));
                }
                if (status.speed) {
                    cout << "Current status: " << status << endl;
                    if (distance(targets.front().p, p) <= config.epsilon) {
                        cout << "Target " << targets.front() <<" achieved!" << endl;
                        status.speed = 0;
                        targets.pop();
                        std::atomic_thread_fence(std::memory_order_release);
                        numTargets.fetch_sub(1, std::memory_order_relaxed);
                    }
                }
            }
            this_thread::sleep_for(PollingFrequency);
        }
    }

    bool ReadConfig(const string filename, BotConfigType& config) {
        ifstream i(filename);
        json j;
        i >> j;

        config.wheelSize = j["WheelSize"];
        config.wheelDist = j["WheelDist"];
        config.epsilon   = j["Epsilon"];
        assert (config.wheelSize);
        assert (config.wheelDist);
        assert (config.epsilon);

        cout << "Read config: Wheel Size = " << config.wheelSize << \
            ", Wheel Dist = " << config.wheelDist << \
            ", Epsilon = " << config.epsilon << endl;
        return true;
    }

    public:
    bool Init(string cfg) {
        engine = async(&Bot::Engine, this);
        controller = async(&Bot::Controller, this);
        assert ( ReadConfig(cfg, config) );
        svr.Get("status", [&](const Request& req, Response& res) {
                string s = to_string(status);
                cout << "Sent status: " << s << endl;
                res.set_content(s, "text/plain");
                });
        svr.Post("/", [&](const Request &req, Response &res) {
                res.set_content("OK", "text/plain");
                BotTargetType t;
                istringstream iss(req.body);
                string token;
                assert ( getline(iss, token, ' '));
                t.p.x = stoi(token);
                assert ( getline(iss, token, ' '));
                t.p.y = stoi(token);
                assert ( getline(iss, token, ' '));
                t.theta = M_PI * stoi(token) / 180;
                assert ( getline(iss, token, ' '));
                t.velocity = stoi(token);
                assert ( getline(iss, token, ' '));
                t.accel = stoi(token);
                targets.emplace(t);
                numTargets.fetch_add(1, std::memory_order_release);
                cout << "Received new target: " << t << endl;
                });
        svr.listen(BOT_HOST, BOT_PORT);
        return true;
    }
};

int main(int argc, char** argv) {
    Bot bot;
    assert ( argc && argv[1] && bot.Init(argv[1]) );
    cout << "DONE" << endl;
    return 0;
}
