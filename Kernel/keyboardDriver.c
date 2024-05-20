#include <keyboard.h>
#include <naiveConsole.h>

#define MAXSIZE 128

static unsigned char buffer[MAXSIZE]={0};
static int bufferPos=0;                     // Indicates your current position in buffer
static int shift = 0;


int isSpecialKey(char key);


int isSpecialKey(char key){
    switch(key) {
        case ESCAPE:
            return 1;

        case L_SHIFT_PRESS:
        case R_SHIFT_PRESS:
            shift = 1;
            return 1; 

        case L_SHIFT_RELEASE:
        case R_SHIFT_RELEASE:
            shift = 0;
            return 1;

    
        case SPACE_BAR:
            //handle mov
            //bufferPos++;
            return 0;

        case TAB:
            //handle mov
            //bufferPos++;
            return 0;

        case ENTER:
            buffer[bufferPos] = 0;
            return 1;
    
        case CAPSLOCK:
            shift = !shift;
            return 1;        
        
        case BACKSPACE:
            // handle delete
            bufferPos--;
            return 1;
        default:
            return 0; 
    }
}

void updateBuffer(){
    uint8_t scancode = getKey();
    
    if(scancode<MAX_SCANCODE){        
        
        char c = scanCodes[shift][scancode];

        if(!isSpecialKey(scancode)){  
            buffer[bufferPos]=c;
            ncPrintChar(buffer[bufferPos]);
            bufferPos++;
            if(bufferPos >= MAXSIZE)
                bufferPos = 0;
        }
    }
    
}

void cleanBuffer(){
    bufferPos=0;
}

char readLastCharacter(){
    if(bufferPos > 1){
        return buffer[bufferPos-1];
    }
    return 0;
}


