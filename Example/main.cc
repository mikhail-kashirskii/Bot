#include <iostream>
#include <controller.h>

int main() {
    BotController C;

    BotTargetType t1 = {100, 0, 0, 10, 1}; //x, y, theta, velocity, accel
    BotTargetType t2 = {100, 150, 0, 10, 1};
    BotTargetType t3 = {0, 150, 0, 10, 1};
    BotTargetType t4 = {0, 0, 0, 10, 1};
    C.Post(t1);
    C.Post(t2);
    C.Post(t3);
    C.Post(t4);
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(1000));
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(2000));
    C.Get("status");
    this_thread::sleep_for(chrono::milliseconds(8000));
    C.Get("status");
    std::cout << "DONE" <<std::endl;
    return 0;
}
