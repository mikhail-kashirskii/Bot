#include "bot.h"

void Bot::Engine() {
	while(1) {
		if (status.speed) {
			double tact = 1.0*EngineFrequency / chrono::seconds(1); 
			double distTact = 2.0*M_PI*config.wheelSize*status.speed * tact; 
			status.p.x += distTact*cos(M_PI*status.theta / 180);
			status.p.y += distTact*sin(M_PI*status.theta / 180);
		}
		this_thread::sleep_for(EngineFrequency);
	}

}
void Bot::Controller() {
	shared_ptr<BotTargetType> target;
	while(1) {
		{
			std::unique_lock<std::mutex> lk(m);
			if(status.speed == 0 && 
				cv.wait_for(lk, PollingFrequency, [this]{return !targets.empty();}))
			{
					target = move(targets.front());
					targets.pop();
					status.speed = target->velocity;
					volatile coord2d_t p = {status.p.x, status.p.y};
					double theta_ = atan((1.0*target->p.y - p.y)/(target->p.x-p.x));
					status.theta = floor(180*theta_/M_PI);
					if ((target->p.x - p.x)<0) {
						status.theta += 180;
					}
			}					
		}
		if (status.speed) {
			cout << "Current status: " << status << endl;
			if (distance(target->p, status.p) <= config.epsilon) {
				cout << "Target " << *target <<" achieved!" << endl;
				status.speed = 0;
			}
			this_thread::sleep_for(PollingFrequency);
		}
	}
}
bool Bot::run(string cfg) {
	bool res = ReadConfig(cfg, config);
	if (res) {
		controller = async(launch::async, &Bot::Controller, this);
		engine = async(launch::async, &Bot::Engine, this);
		server = async(launch::async, &Bot::Server, this);
		server.wait();
		engine.wait();
		controller.wait();
	}
	return res;
}

int main(int argc, char** argv) {
    Bot bot;
    bool result = argc && argv[1] && bot.run(argv[1]);
    cout << "DONE " << result << endl;
    return result == true;
}
