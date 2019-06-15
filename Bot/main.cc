#include <iostream>
#include <httplib.h>
#include <config.h>

using namespace httplib;

class Bot {
    Server svr;
    BotConfigType config;
    public:
    bool Init(std::string cfg) {
        assert ( ReadConfig("../configs/config.json", config) );
        svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
                auto numbers = req.matches[1];
                res.set_content(numbers, "text/plain");
                });
        svr.Get("status", [&](const Request& req, Response& res) {
                string s = "status!";
                res.set_content(s, "text/plain");
                });
        svr.Post("/", [&](const Request &req, Response &res) {
                std::cout << req.body <<std::endl;
                res.set_content("OK", "text/plain");
                });

        svr.listen("localhost", 1234);
        return true;
    }
};

int main() {
    Bot bot;
    assert ( bot.Init("../configs/config.json") );
    std::cout << "DONE" <<std::endl;
    return 0;
}
