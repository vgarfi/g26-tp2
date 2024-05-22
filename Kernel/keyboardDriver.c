#include <keyboard.h>
#include <naiveConsole.h>

#define MAXSIZE 128

#define UP_ARROW_VAL        0xE0
#define LEFT_ARROW_VAL      0xE1
#define DOWN_ARROW_VAL      0xE2
#define RIGHT_ARROW_VAL     0xE3

static unsigned char buffer[MAXSIZE] = {0};
static int bufferPos = 0;
static int readPos = 0;
static int shift = 0;
static int dataStatus = 0;

int shiftHandler(uint8_t key){
    switch(key) {
        case L_SHIFT_PRESS:
        case R_SHIFT_PRESS:
            shift = 1;
            return 1; 
            
        case L_SHIFT_RELEASE:
        case R_SHIFT_RELEASE:
            shift = 0;
            return 1;

        default:
            return 0; 
    }
}

uint8_t isArrow (uint8_t key) {
    switch (key)
    {
    case UP_ARROW:
        return UP_ARROW_VAL;
    
    case LEFT_ARROW:
        return LEFT_ARROW_VAL;

    case DOWN_ARROW:
        return DOWN_ARROW_VAL;
    
    case RIGHT_ARROW:
        return RIGHT_ARROW_VAL;

    default:
        return 0;
    }    
}

void updateBuffer() {
    uint8_t scancode = getKey();
    uint8_t arrowValue = isArrow(scancode);
    
    if(arrowValue || (!shiftHandler(scancode) && scancode < MAX_SCANCODE)) { // Agregamos los caracteres, con su modificación correspondiente ante un shift
        dataStatus = 1;
        char c = (arrowValue != 0)? arrowValue : scancodesChars[shift][scancode];
        bufferPos = bufferPos % MAXSIZE;
        buffer[bufferPos++] = c;
        ncPrintChar(c); // TODO simplemente eliminar esto
    }
}

int isBufferEmpty(){
    return bufferPos == 0;
}

void cleanBuffer(){
    bufferPos = 0;
}

unsigned char readBuf () {
    if(isBufferEmpty())
        return 0;
    readPos = readPos % MAXSIZE;
    return buffer[readPos++];
}

char readLastCharacter() {
    if(dataStatus)
        if(bufferPos > 1){
            return buffer[bufferPos-1];
        }
        else {
            return buffer[MAX_SCANCODE-1];
        }
    return 0;
}