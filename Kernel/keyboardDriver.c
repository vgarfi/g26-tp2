#include <keyboard.h>
#include <naiveConsole.h>

#define MAXSIZE 128

static unsigned char buffer[MAXSIZE]={0};
static int bufferPos=0;                     // Indicates your current position in buffer

void updateBuffer(){
    uint8_t key = getKey();
    
    buffer[bufferPos]=scanCodes[key];
    ncPrintChar(buffer[bufferPos]);
    bufferPos++;
}

void cleanBuffer(){
    bufferPos=0;
}
