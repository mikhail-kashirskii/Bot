# Bot

Example application
--------------
```c++
#include <iostream>
#include <controller.h>

int main() {
    BotController C;

    BotTargetType t1 = {100, 42, 0, 10, 1}; //x, y, theta, velocity, accel
    BotTargetType t2 = {120, 150, 0, 10, 1}; //x, y, theta, velocity, accel
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
    $ build/Example/example 
```

Expected output (status format: X, Y, Theta, Speed)

```c++
Got status: 0 0 0 0
Got status: 20 8 22 10
Got status: 70 28 22 10
Got status: 119 154 79 0
```

Expected output on the Bot side:

```c++
Read config: Wheel Size = 1, Wheel Dist = 4, Epsilon = 5
Received new target: 100 42 0 10 1
Received new target: 120 150 0 10 1
Sent status: 0 0 0 0
Current status: 0 0 22 10
Current status: 5 2 22 10
Current status: 10 4 22 10
Current status: 15 6 22 10
Current status: 20 8 22 10
Sent status: 20 8 22 10
Current status: 25 10 22 10
Current status: 30 12 22 10
Current status: 35 14 22 10
Current status: 40 16 22 10
Current status: 45 18 22 10
Current status: 50 20 22 10
Current status: 55 22 22 10
Current status: 60 24 22 10
Current status: 65 26 22 10
Sent status: 70 28 22 10
Current status: 70 28 22 10
Current status: 75 30 22 10
Current status: 80 32 22 10
Current status: 85 34 22 10
Current status: 90 36 22 10
Current status: 95 38 22 10
Current status: 100 40 22 10
Target 100 42 0 10 1 achieved!
Current status: 100 40 79 10
Current status: 101 46 79 10
Current status: 102 52 79 10
Current status: 103 58 79 10
Current status: 104 64 79 10
Current status: 104 64 79 10
Current status: 106 76 79 10
Current status: 106 76 79 10
Current status: 108 88 79 10
Current status: 109 94 79 10
Current status: 110 100 79 10
Current status: 111 106 79 10
Current status: 112 112 79 10
Current status: 112 112 79 10
Current status: 113 118 79 10
Current status: 114 124 79 10
Current status: 115 130 79 10
Current status: 116 136 79 10
Current status: 117 142 79 10
Current status: 119 154 79 10
Target 120 150 0 10 1 achieved!
Sent status: 119 154 79 0
```
