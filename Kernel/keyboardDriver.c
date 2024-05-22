#include <keyboard.h>
#include <naiveConsole.h>

#define MAXSIZE 128

static unsigned char buffer[MAXSIZE] = {0};
static int bufferPos = 0;
static int readPos = 0;
static int shift = 0;

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

int isArrow (uint8_t key) {
    return key == UP_ARROW || key == LEFT_ARROW || key == DOWN_ARROW || key == RIGHT_ARROW;
}

void updateBuffer(){
    
    uint8_t scancode = getKey();
     int isArrowValue = isArrow(scancode);
     
    if(isArrowValue || (!shiftHandler(scancode) && scancode < MAX_SCANCODE)) { // Agregamos los caracteres, con su modificación correspondiente ante un shift
        char c =  isArrowValue? scancode : scancodesChars[shift][scancode];
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
    if(bufferPos > 1){
        return buffer[bufferPos-1];
    }
    return 0;
}