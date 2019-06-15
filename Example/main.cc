#include <iostream>
#include <controller.h>

int main() {
    BotController C;

    BotTargetType t = {100, 100, 0, 10, 1};
    assert ( C.Post(t) );
    assert ( C.Get("status") );
    std::cout << "DONE" <<std::endl;
    return 0;
}
