#ifndef BOT_UTILS_H
#define BOT_UTILS_H
#include <cstdint>
#include <cmath>

using namespace std;

#define BOT_HOST "localhost"
#define BOT_PORT 1234

typedef uint32_t coord_t; 
typedef struct {
    coord_t x;
    coord_t y;
} coord2d_t; 

typedef struct {
    coord2d_t p;
    coord_t theta;
    coord_t velocity;
    coord_t accel;
} BotTargetType;

template<typename T>
struct  BotStatusType{
    struct p{
        T x;
        T y;
        p():x(0), y(0){}
    } p;
    T theta;
    T speed;
    BotStatusType():theta(0), speed(0){}
};

ostream& operator<<(ostream& os, const BotTargetType& t)
{
    os << t.p.x << " " << t.p.y << " " << t.theta \
       << " " << t.velocity << " " << t.accel;
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const BotStatusType<T>& t)
{
    os << t.p.x << " " << t.p.y << " " << t.theta \
       << " " << t.speed;
    return os;
}

template<typename T> std::string to_string(const T &t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

static inline coord_t distance(coord2d_t &a, coord2d_t &b) {    
    coord_t c1 = b.x-a.x;
    coord_t c2 = b.y-a.y;
    return std::sqrt(c1*c1+c2*c2);
}
#endif
