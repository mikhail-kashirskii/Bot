#ifndef BOT_UTILS_H
#define BOT_UTILS_H
#include <cstdint>

using namespace httplib;
using namespace std;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t theta;
    uint32_t velocity;
    uint32_t acces;
} BotTargetType;


ostream& operator<<(ostream& os, const BotTargetType& t)
{
    os << t.x << " " << t.y;
    return os;
}

template<typename T> std::string to_string(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
#endif
