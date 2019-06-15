#include <iostream>
#include <queue>
#include <httplib.h>
#include <config.h>
#include <utils.h>

using namespace httplib;

class Bot {
    Server svr;
    BotConfigType config;
    std::queue<BotTargetType> targets;
    BotStatusType status;

    public:
    bool Init(std::string cfg) {
        assert ( ReadConfig(cfg, config) );
        svr.Get("status", [&](const Request& req, Response& res) {
                string s = to_string(status);
                std::cout << "Sent status: " << s << std::endl;
                res.set_content(s, "text/plain");
                });
        svr.Post("/", [&](const Request &req, Response &res) {
                res.set_content("OK", "text/plain");
                BotTargetType t;
                std::istringstream iss(req.body);
                std::string token;
                assert ( std::getline(iss, token, ' '));
                t.x = std::stoi(token);
                assert ( std::getline(iss, token, ' '));
                t.y = std::stoi(token);
                assert ( std::getline(iss, token, ' '));
                t.theta = std::stoi(token);
                assert ( std::getline(iss, token, ' '));
                t.velocity = std::stoi(token);
                assert ( std::getline(iss, token, ' '));
                t.accel = std::stoi(token);
                targets.emplace(t);
                std::cout << "Received new target: " << t << std::endl;
                });

        svr.listen("localhost", 1234);
        return true;
    }
};

int main(int argc, char** argv) {
    Bot bot;
    assert ( argc && argv[1] && bot.Init(argv[1]) );
    std::cout << "DONE" <<std::endl;
    return 0;
}
