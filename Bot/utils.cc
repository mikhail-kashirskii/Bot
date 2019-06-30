#include <httplib.h>
#include <nlohmann/json.hpp>
#include "bot.h"

using Request = httplib::Request;
using Response = httplib::Response;
using json = nlohmann::json;

bool Bot::ReadConfig(const string filename, BotConfigType& config) {
	ifstream i(filename);
	json j;
	i >> j;

	config.wheelSize = j["WheelSize"];
	config.wheelDist = j["WheelDist"];
	config.epsilon   = j["Epsilon"];

	cout << "Read config: Wheel Size = " << config.wheelSize << \
		", Wheel Dist = " << config.wheelDist << \
		", Epsilon = " << config.epsilon << endl;
	return config.wheelSize && config.wheelDist && config.epsilon;
}

void Bot::Server() {
	httplib::Server svr;
	svr.Get("status", [&](const Request& req, Response& res) {
			string s = to_string(status);
			cout << "Sent status: " << s << endl;
			res.set_content(s, "text/plain");
			});
	svr.Post("/", [&](const Request &req, Response &res) {
			res.set_content("OK", "text/plain");
			auto t = new BotTargetType();
			istringstream iss(req.body);
			string token;
			getline(iss, token, ' ');
			t->p.x = stoi(token);
			getline(iss, token, ' ');
			t->p.y = stoi(token);
			getline(iss, token, ' ');
			t->theta = M_PI * stoi(token) / 180;
			getline(iss, token, ' ');
			t->velocity = stoi(token);
			getline(iss, token, ' ');
			t->accel = stoi(token);
			{
				std::lock_guard<std::mutex> lk(m);
				targets.push(unique_ptr<BotTargetType>(t));
			}
			cv.notify_one();
			cout << "Received new target: " << *t << endl;
			});
	svr.listen(BOT_HOST, BOT_PORT);
}
