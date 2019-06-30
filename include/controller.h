#pragma once
#include <mutex>
#include <httplib.h>
#include <bot-types.h>

using namespace std;
using namespace httplib;

class BotController {
    Client cli;
    public:
    BotController(): cli(BOT_HOST, BOT_PORT) {};

    bool Get(string str) {
        auto res = cli.Get(str.c_str());
        if (res && res->status == 200) {
            cout << "Got " << str << ": " << res->body << endl;
            return true;
        }
        return false;
    }

    bool Post(BotTargetType &t) {
        string str = to_string(t);
        auto res = cli.Post("/", str.c_str(), "text/plain");
        return res && res->status == 200 && res->body == "OK";
    }
};
