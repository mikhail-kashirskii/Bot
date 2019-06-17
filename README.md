# Bot

Instruction to compile and run.
1. Compile the project and run the Bot:
    $ mkdir build && cd build && cmake .. && make -j4 all && Bot/bot ../configs/config.json

Expected output (Config read and the Bot is ready):
    Read config: Wheel Size = 10, Wheel Dist = 10, Epsilon = 3

2. Use another console to run the example application to send the commands to the Bot and get its status:
    $ Example/example 

Expected output (status format: X, Y, Theta, Speed)
    Got status: 0 0 0 0
    Got status: 50 50 0 10
    Got status: 130 130 0 10
    Got status: 200 200 0 0

Expected output on the Bot side:
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

