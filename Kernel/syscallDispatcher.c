#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <time.h>
#include <keyboard.h>
#include <interrupts.h>

int nanosleep(uint64_t rdi);     // rdi : seconds, rsi : miliseconds
int saveregs(void);
int read(uint64_t fd, char * buf, uint64_t count);

void saveRegsInBuffer(uint64_t* buf);

uint64_t registers[17]={0};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    switch(rax){
        case 0: return read(rdi, (char *)rsi, rdx);
        case 3: return saveregs();
        case 162: return nanosleep(rdi);
        default: return -1;
    }
}

int read(uint64_t fd, char * buf, uint64_t count){
    if(fd!=STDIN){   // Only can read from standard input
        return 0;
    }
    uint64_t sizeRead=0;
    unsigned char lastRead='\0';
    while(sizeRead!=count && lastRead!='\n'){
        if(!isBufferEmpty()){   // If there are chars in buffer, we read them
            lastRead=readBuf();
            buf[sizeRead++]=lastRead;
        }else{                  // If not, we halt until more data is inserted 
            _hlt();
        }
    }
    return sizeRead==count?count:sizeRead-1;    // If we return sizeRead-1 it means we stopped at '\n'
}

/** registers is a buffer of 17 qwords to save registers in the next order:
 *  RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 RIP
 */
int saveregs(){
    saveRegsInBuffer(registers);
    return 0;
}

int nanosleep(uint64_t rdi){
    if(rdi<0)
        return -1;
    sleep(rdi);
    return 0;
}

