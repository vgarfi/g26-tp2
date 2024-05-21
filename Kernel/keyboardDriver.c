#include <keyboard.h>
#include <naiveConsole.h>

#define MAXSIZE 128

static unsigned char buffer[MAXSIZE]={0};
static int bufferPos=0;                     // Indicates your current position in buffer
static int shift = 0;

int specialKeyHandler(uint8_t key){
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

        case TAB:
            //handle mov
            bufferPos++;
            return 1;

        case ENTER:
            buffer[bufferPos] = 0;
            return 1;
    
        /*case CAPSLOCK:
            shift = !shift;
            return 1;  */      
        
        case BACKSPACE:
            // handle delete (imprime espacio periodic)
            bufferPos--;
            return 1;
        default:
            return 0; 
    }
}

void updateBuffer(){
    uint8_t scancode = getKey();
          
    if(!specialKeyHandler(scancode) && scancode < MAX_SCANCODE){  
            char c = scanCodes[shift][scancode];
            buffer[bufferPos]=c;
            ncPrintChar(buffer[bufferPos]);
            bufferPos++;
            if(bufferPos >= MAXSIZE)
                bufferPos = 0;
    }
    
}

int isBufferEmpty(){
    return bufferPos==0;
}

void cleanBuffer(){
    bufferPos=0;
}

unsigned char readBuf(){
    if(isBufferEmpty())
        return 0;
    unsigned char ans = buffer[0];
    for(int i=0; i<bufferPos-1; i++)
        buffer[i]=buffer[i+1];
    bufferPos--;
    return ans;
}

char readLastCharacter(){
    if(bufferPos > 1){
        return buffer[bufferPos-1];
    }
    return 0;
}


