#ifndef BOT_CONFIG_H
#define BOT_CONFIG_H
#include <cstdint>
#include <nlohmann/json.hpp>
#include <cassert>
using json = nlohmann::json;
using namespace std;

typedef struct {
    uint32_t wheelSize;
    uint32_t wheelDist;
    uint32_t epsilon;
} BotConfigType;

bool ReadConfig(const string filename, BotConfigType& config) {
    ifstream i(filename);
    json j;
    i >> j;

    config.wheelSize = j["WheelSize"];
    config.wheelDist = j["WheelDist"];
    config.epsilon   = j["Epsilon"];
    assert (config.wheelSize);

    cout << "Wheel Size = " << j["WheelSize"] << endl;
    cout << "Wheel Dist = " << j["WheelDist"] << endl;
    cout << "Epsilon = " << j["Epsilon"] << endl;
    return true;
}
#endif
