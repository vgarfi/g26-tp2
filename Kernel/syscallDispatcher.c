#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <time.h>

int nanosleep(uint64_t rdi);     // rdi : seconds, rsi : miliseconds

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    switch(rax){
        case 162: return nanosleep(rdi);
        default: return -1;
    }
}

int nanosleep(uint64_t rdi){
    if(rdi<0)
        return -1;
    sleep(rdi);
    return 0;
}