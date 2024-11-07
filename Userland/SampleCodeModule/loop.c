#include "include/loop.h"
#include "include/syscalls.h"
#include "include/stdio.h"

int64_t loop_process(int argc, char** argv) {
    int printed;
    while(printed != EOF) {
        sysSleep(2, 0);
        print("\n");
        print("Hello (from ");
        printColor("LOOP", 0x0000D4C1);
        printed = printf(") with PID: %d ", sysGetCurrentPid(),0,0);
    }
    return 0;
}
