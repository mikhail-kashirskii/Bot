#include <iostream>
#include <httplib.h>
#include <config.h>

int main() {
    using namespace httplib;
    Server svr;
    BotConfigType config;
    ReadConfig("../config.json", config);

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });
    svr.Post("/post", [&](const Request &req, Response &res) {
            std::cout << req.body <<std::endl;
            res.set_content("test", "text/plain");
    });

    svr.listen("localhost", 1234);
    std::cout << "DONE" <<std::endl;
    return 0;
}
