#include <iostream>
#include <controller.h>

int main() {
    BotController C;

    BotTargetType t1 = {100, 42, 0, 10, 1}; //x, y, theta, velocity, accel
    BotTargetType t2 = {120, 150, 0, 10, 1}; //x, y, theta, velocity, accel
    C.Post(t1);
    C.Post(t2);
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(500));
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(1000));
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(3000));
    C.Get("status");
    std::cout << "DONE" <<std::endl;
    return 0;
}
