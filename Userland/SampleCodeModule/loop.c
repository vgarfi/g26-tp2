// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/loop.h"
#include "include/syscalls.h"
#include "include/stdio.h"

int64_t loopProcess(int argc, char** argv) {
    int printed = 0;
    while(printed != EOF) {
        sysSleep(1, 1);
        print("Hello (from ");
        printColor("LOOP", 0x0000D4C1);
        printf(") with PID: %d ", sysGetCurrentPid(),0,0);
        printed = print("\n");
    }
    return 0;
}
