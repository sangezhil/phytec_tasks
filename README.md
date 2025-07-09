WEEK-1
TOPIC:

                   1) C Core Concept
                   2) OSI Model
                   3) StateMachine
                  4) Array,Pointer,Event
                  5) Queue, Linked List, Circular Buffer

1) Documentation of OSI Model 
2) Implementation of Queue, Linked List, Circular Buffer
3) UDP Chat App
    i) Send/Receive Message
    ii) Using CommandLine Arugments

CHAT APP STEP BY STEP RUNNING PROCESS :  

1) To Compaile the Both Server and Client Source file
    i) gcc server.c -o server
    ii) gcc client.c -o client
2) To run the both Object file with the Port and Loopback IP address
    i) ./server 5050
    ii) ./client 127.0.0.1 5050
3) To Pass the Message Client to Server and Server to Client

week-2
TOPIC:
            Porting Contiki-NG to EFR32ZG28 (ARM Cortex-M0+):
            >>Porting Contiki-NG to EFR32ZG28 Platform:
    Objective:
                To enable Contiki-NG RTOS on the EFR32ZG28 SoC (Cortex-M0+) by:
                      • Creating a new platform definition under arch/platform/efr32zg28/
                      • Building and running a sample application (LED blink)
    Target Platform Details:
                     Component
                       >>CPU Core - ARM Cortex-M0+
                       >>RTOS    - Contiki-NG
                      >>Toolchain - arm-none-eabi-gcc
    Structure Setup:
                    
contiki-ng/
├── arch/
│   ├── cpu/
│   │   └── efr32/
│   │       ├── efr32.c
│   │       ├── efr32-clocks.c
│   │       └── efr32-startup.c
│   └── platform/
│       └── efr32zg28/
│           ├── platform-conf.h
│           ├── contiki-conf.h
│           ├── efr32zg28.c
│           ├── leds-arch.c
│           ├── syscalls.c
│           ├── gpio-hal-arch.c
│           ├── startup_efr32zg28.S
│           ├── efr32zg28.ld
│           └── Makefile.platform
├── examples/
│   └── efr32zg28/
│       └── led_blink.c

Build Process:
>>cd contiki-ng/examples/efr32zg28/
>>make clean
>>make TARGET=efr32zg28 led_blink V=1

