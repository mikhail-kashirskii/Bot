#ifndef BOT_CONTROLLER_H
#define BOT_CONTROLLER_H
#include <httplib.h>
#include <utils.h>

using namespace httplib;

class BotController {
    Client cli;
    public:
    BotController(): cli("localhost", 1234) {};

    bool Get(std::string str) {
        auto res = cli.Get(str.c_str());
        if (res && res->status == 200) {
            std::cout << "Got " << str << ": " << res->body << std::endl;
            return true;
        }
        return false;
    }

    bool Post(BotTargetType &t) {
        std::string str = to_string(t);
        auto res = cli.Post("/", str.c_str(), "text/plain");
        return res && res->status == 200 && res->body == "OK";
    }


};
#endif
