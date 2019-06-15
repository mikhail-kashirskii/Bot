#ifndef BOT_UTILS_H
#define BOT_UTILS_H
#include <cstdint>

using namespace std;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t theta;
    uint32_t velocity;
    uint32_t accel;
} BotTargetType;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t theta;
    uint32_t speed;
} BotStatusType;

ostream& operator<<(ostream& os, const BotTargetType& t)
{
    os << t.x << " " << t.y << " " << t.theta \
       << " " << t.velocity << " " << t.accel;
    return os;
}

ostream& operator<<(ostream& os, const BotStatusType& t)
{
    os << t.x << " " << t.y << " " << t.theta \
       << " " << t.speed;
    return os;
}

template<typename T> std::string to_string(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
#endif
