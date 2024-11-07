#include "include/loop.h"
#include "include/stdio.h"

void basic_sleep(void);

int64_t loop_process(int argc, char** argv) {
    int printed;
    while(printed != -1) {
        basic_sleep();
        printed = print("\n");
        print("Hello (from ");
        printColor("LOOP", 0x0000D4C1);
        printf(") with PID: %d ", sysGetCurrentPid(),0,0);
        print("\0");
    }
    return 0;
}

void basic_sleep(void) {
    for (int i = 0; i < 20000000; i++);
}
