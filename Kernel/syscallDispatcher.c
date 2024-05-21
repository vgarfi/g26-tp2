#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <time.h>

int nanosleep(uint64_t rdi);     // rdi : seconds, rsi : miliseconds
int saveregs(uint64_t rdi);

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    switch(rax){
        case 3: return saveregs(rdi);
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

/** rdi stores a buffer direction of 17 qwords to save registers in the next order:
 *  RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 RIP
 */
int saveregs(uint64_t rdi){
    saveRegsInBuffer(rdi);
    return 0;
}