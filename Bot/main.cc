#include <iostream>
#include <queue>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <future>
#include <bot-types.h>

using namespace httplib;
using json = nlohmann::json;

class Bot {
    typedef struct {
        coord_t wheelSize;
        coord_t wheelDist;
        coord_t epsilon;
    } BotConfigType;

    Server svr;
    BotConfigType config;
    queue<BotTargetType> targets;
    BotStatusType<atomic<coord_t>> status;
    std::future<void> engine;
    std::future<void> controller;

    void Engine() {
        while(1) {
            if (status.speed) {
                status.p.x += status.speed;
                status.p.y += status.speed;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }

    }
    void Controller() {
        while(1) {
            if (status.speed == 0 && !targets.empty()) {
                status.speed = targets.front().velocity;
            }
            if (status.speed) {
                cout << "Current status: " << status << endl;
                coord2d_t p = {status.p.x, status.p.y};
                if (distance(targets.front().p, p)   <= config.epsilon) {
                    cout << "Target " << targets.front() <<" achieved!" << endl;
                    status.speed = 0;
                    targets.pop();
                }
            }
            this_thread::sleep_for(chrono::milliseconds(100));
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
                t.theta = stoi(token);
                assert ( getline(iss, token, ' '));
                t.velocity = stoi(token);
                assert ( getline(iss, token, ' '));
                t.accel = stoi(token);
                targets.emplace(t);
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
