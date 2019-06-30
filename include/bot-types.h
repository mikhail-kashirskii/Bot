#pragma once
#include <cstdint>
#include <cmath>
#include <sstream>
#include <future>
#include <memory> 
#include <queue>

using namespace std;

#define BOT_HOST "localhost"
#define BOT_PORT 1234

typedef uint32_t coord_t; 
typedef struct {
    coord_t x;
    coord_t y;
} coord2d_t; 

typedef struct BotTargetType {
    coord2d_t p;
    double theta;
    coord_t velocity;
    coord_t accel;
	BotTargetType() = default;
	BotTargetType (const BotTargetType&) = delete;
	BotTargetType& operator=(const BotTargetType&) = delete;
	BotTargetType& operator=(const BotTargetType&) volatile = delete;
} BotTargetType;

template<typename T>
struct  BotStatusType{
    struct p{
        T x;
        T y;
        p():x(0), y(0){}
    } p;
    double theta;
    T speed;
    BotStatusType():theta(0), speed(0){}
};

static ostream& operator<<(ostream& os, const BotTargetType& t)
{
    os << t.p.x << " " << t.p.y << " " << floor(180*t.theta/M_PI) \
       << " " << t.velocity << " " << t.accel;
    return os;
}

template<typename T>
static ostream& operator<<(ostream& os, const BotStatusType<T>& t)
{
    os << t.p.x << " " << t.p.y << " " << floor(180*t.theta/M_PI) \
       << " " << t.speed;
    return os;
}

template<typename T> std::string to_string(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template<typename T1, typename T2>
static inline coord_t distance(T1 &a,T2 &b) {    
    coord_t c1 = b.x-a.x;
    coord_t c2 = b.y-a.y;
    return std::sqrt(c1*c1+c2*c2);
}
