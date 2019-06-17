# Bot

Example application
--------------
```c++
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
```

Instruction to compile and run.
--------------
1. Compile the project and run the Bot:

```c++
    $ mkdir build && cd build && cmake .. && make -j4 all && Bot/bot ../configs/config.json
```

Expected output (Config read and the Bot is ready):

    Read config: Wheel Size = 10, Wheel Dist = 10, Epsilon = 3

2. Use another console to run the example application to send the commands to the Bot and get its status:

```c++
    $ Example/example 
```

Expected output (status format: X, Y, Theta, Speed)

```c++
Got status: 0 0 0 0
Got status: 50 50 0 10
Got status: 130 130 0 10
Got status: 200 200 0 0
```

Expected output on the Bot side:

```c++
Received new target: 100 100 0 10 1
Received new target: 200 200 0 10 1
Sent status: 0 0 0 0
Current status: 0 0 0 10
Current status: 10 10 0 10
Current status: 20 20 0 10
Current status: 30 30 0 10
Current status: 40 40 0 10
Sent status: 50 50 0 10
Current status: 50 50 0 10
Current status: 60 60 0 10
Current status: 70 70 0 10
Current status: 80 80 0 10
Current status: 90 90 0 10
Current status: 100 100 0 10
Target 100 100 0 10 1 achieved!
Current status: 100 100 0 10
Current status: 110 110 0 10
Current status: 120 120 0 10
Sent status: 130 130 0 10
Current status: 130 130 0 10
Current status: 140 140 0 10
Current status: 150 150 0 10
Current status: 160 160 0 10
Current status: 170 170 0 10
Current status: 180 180 0 10
Current status: 190 190 0 10
Current status: 200 200 0 10
Target 200 200 0 10 1 achieved!
Sent status: 200 200 0 0
```

