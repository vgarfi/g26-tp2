#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include "include/time.h"
#include <keyboard.h>
#include <interrupts.h>

int nanosleep(uint64_t secs, uint64_t ticks);     // rdi : seconds, rsi : miliseconds
int saveregs(void);
int read(uint64_t fd, char * buf, uint64_t count);
int write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor);
int sound(uint64_t ticks);
char * time(void);
char * date(void);
int incSize();
int decSize();

void saveRegsInBuffer(uint64_t* buf);

uint64_t registers[17]={0};

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    switch(rax){
        case 0: return read(rdi, (char *)rsi, rdx);
        case 1: return write(rdi, (char *)rsi, rdx, r10);
        case 3: return saveregs();
        case 5: return time();
        case 6: return date();
        case 7: return incSize();
        case 8: return decSize();
        case 20: return upArrowValue();
        case 21: return leftArrowValue();
        case 22: return downArrowValue();
        case 23: return rightArrowValue();
        case 30: return clearScreen();
        case 32: return printSquare(rdi, rsi,rdx,r10);
        case 31: return printRect(rdi,rsi,rdx,r10,r8);
        case 40: return setCursor(rdi, rsi);
        case 128: return sound(rdi);
        case 162: return nanosleep(rdi, rsi);
        default: return -1;
    }
}

int read(uint64_t fd, char * buf, uint64_t count) {
    if(fd!=STDIN) {   // Only can read from standard input
        return 0;
    }
    uint64_t sizeRead=0;
    unsigned char lastRead='\0';
    int startTick = ticks_elapsed();
    while(sizeRead!=count && ticks_elapsed() <= startTick){
        if(!isBufferEmpty()) {   // If there are chars in buffer, we read them
            lastRead = readBuf();
            buf[sizeRead++] = lastRead;
        }else{                  // If not, we halt until more data is inserted 
            _hlt();
        }
    }
    return sizeRead == count? count : sizeRead;    // If we return sizeRead-1 it means we stopped at '\n'
}

int write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor){
    if(fd!=STDOUT)  // Only can write in STDOUT
        return 0;
    int i;
    char toPrint[2]={0,0};
    for(i=0; i<count; i++){
        toPrint[0]=buf[i];
        vdPrint(toPrint, hexColor);
    }
    return i;
}

int upArrowValue() {    
    return kbUpArrowValue();
}

int leftArrowValue() {
    return kbLeftArrowValue();
}

int downArrowValue() {
    return kbDownArrowValue();
}

int rightArrowValue() {
    return kbRightArrowValue();
}

int clearScreen() {
    vdClearScreen();
    vdClearBuffer();
    return 0;
}

int printRect(int x,int y,int base,int height,uint32_t hexColor) {
    vdPrintRect(x,y,base,height,hexColor);
    return 0;
}

int printSquare (int x, int y,int side, uint32_t hexColor){
    vdPrintSquare(x,y,side, hexColor);
    return 0;
}

int setCursor(uint64_t x, uint64_t y) {
    vdSetCursor(x, y);
    return 0;
}

/** registers is a buffer of 17 qwords to save registers in the next order:
 *  RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 RIP
 */
int saveregs(){
    saveRegsInBuffer(registers);
    return 0;
}

int sound(uint64_t ticks){
    beep(ticks);
    return 0;
}

// rdi = seconds, rsi = ticks
int nanosleep(uint64_t secs, uint64_t ticks){
    if(secs<0 || ticks<0)
        return -1;
    int secondsToTicks = secs*18, msToTicks=ticks;
    int totalTicks = secondsToTicks + msToTicks;
    sleep(totalTicks);
    return 0;
}

char * time(void){
    return getCurrentTime();
}

char * date(void){
    return getCurrentDate();
}


int incSize(){
    int zoomFail = sizeUp();
    if(!zoomFail)
        resize();
    return zoomFail;
}

int decSize(){
    int zoomFail = sizeDown();
    if(!zoomFail)
        resize();
    return zoomFail;
}