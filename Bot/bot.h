#pragma once
#include <iostream>
#include <future>
#include <bot-types.h>

class Bot {
    const chrono::milliseconds PollingFrequency = chrono::milliseconds(100);
    const chrono::milliseconds EngineFrequency = chrono::milliseconds(100);
    typedef struct {
        coord_t wheelSize;
        coord_t wheelDist;
        coord_t epsilon;
    } BotConfigType;

    BotConfigType config;
    queue<unique_ptr<BotTargetType>> targets;
    BotStatusType<atomic<coord_t>> status;
    std::future<void> engine;
    std::future<void> controller;
    std::future<void> server;
	std::mutex m;
	std::condition_variable cv;

    void Engine();
    void Controller();
    void Server();

    bool ReadConfig(const string filename, BotConfigType& config);
public:
    bool run(string cfg);
};

