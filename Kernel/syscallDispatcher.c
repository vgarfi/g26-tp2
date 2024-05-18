#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>

static uint64_t(*syscallHandlers[])(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8)={

};         // Handlers for syscalls, e.g. read, write, etc

static int handlersSize=sizeof(syscallHandlers)/sizeof(syscallHandlers[0]);

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    if(rax < handlersSize && syscallHandlers[rax]!=NULL)                                                            // Compares with NULL in case it is not implemented yet
        return syscallHandlers[rax](rdi,rsi,rdx,r10,r8);
    return -1;
}