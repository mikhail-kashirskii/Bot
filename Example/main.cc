#include <iostream>
#include <controller.h>

int main() {
    BotController C;

    BotTargetType t1 = {100, 100, 0, 10, 1}; //x, y, theta, velocity, accel
    BotTargetType t2 = {200, 200, 0, 10, 1}; //x, y, theta, velocity, accel
    assert ( C.Post(t1) );
    assert ( C.Post(t2) );
    assert ( C.Get("status") );
    this_thread::sleep_for(chrono::milliseconds(500));
    assert ( C.Get("status") );
    this_thread::sleep_for(chrono::milliseconds(1000));
    assert ( C.Get("status") );
    this_thread::sleep_for(chrono::milliseconds(3000));
    assert ( C.Get("status") );
    std::cout << "DONE" <<std::endl;
    return 0;
}
