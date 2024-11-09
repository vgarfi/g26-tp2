#include "include/loop.h"
#include "include/syscalls.h"
#include "include/stdio.h"

int64_t loopProcess(int argc, char** argv) {
    int printed;
    while(printed != EOF) {
        // sysBeepSound(2, 450);
        sysSleep(0, 2);
        // for (int i = 0; i < 18*3000; i++) {
        // for (int i = 0; i < 18*80; i++)
        //     {
        //         /* code */
        //     }
        // }
        print("Hello (from ");
        printColor("LOOP", 0x0000D4C1);
        printf(") with PID: %d ", sysGetCurrentPid(),0,0);
        printed = print("\n");
    }
    return 0;
}
