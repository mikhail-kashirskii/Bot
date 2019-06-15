#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <utils.h>

using namespace httplib;
int main() {
    httplib::Client cli("localhost", 1234);

    auto res = cli.Get("/numbers/1234"); 
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
    BotTargetType t;
    t.x = 1;
    t.y = 2;
    std::string str=to_string(t);
    std::cout << str <<std::endl;
    res = cli.Post("/post", str.c_str(), "text/plain");
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
    std::cout << "DONE" <<std::endl;
    return 0;
}
