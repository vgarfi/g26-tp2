#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/colors.h"
#include "include/string.h"
#include "include/lib.h"

#define MAXBUFLEN 100
#define MINLEN 2
#define MAX_INPUTS_STORE    10

/**
 * readSizeFlag is used as a way of identifying whether
 * getChar returned with no value read because of timeout
 * or not
*/
static int readSizeFlag = 0;

static int ctrlFlag = 0, checkZoomFlag;

static uint64_t hexcol = DEFAULT;   // default shell color

static int isPrintable(unsigned char c);
static int isVerticalArrow(unsigned char c);

static char inputs[MAX_INPUTS_STORE][MAXBUFLEN];
static int inputIndex = 0;

unsigned char getchar(void){
    unsigned char read = 0;
    
    int pid = sysGetCurrentPid();
    int fd = sysGetReadFileDescriptor(pid);
    TScope scope = sysGetScope(pid);

    if (fd == -1 || (fd == STDIN && scope == BACKGROUND)) {
        return 0;
    }

    readSizeFlag = sysRead(fd, &read, 1);
    return read;
}

unsigned char putchar(unsigned char c){
    int fd = sysGetWriteFileDescriptor(sysGetCurrentPid());
    if (fd == -1) {
        return 0;
    }
    sysWrite(fd, &c, 1, hexcol);
    return c;
}

int printColor(char* str, uint64_t hexColor){
    int pid = sysGetCurrentPid();
    TScope scope = sysGetScope(pid);
    if (scope == -1) {
        return 0;
    }
    hexcol = hexColor;
    int i;
    if (scope == BACKGROUND && sysGetWriteFileDescriptor(pid) == STDOUT) {
        hexcol = LOWKEY;
        sysWrite(STDOUT, "    ", 5, hexcol); // TODO ver si podemos hacer que esto se imprima por cada vez que se hace nueva linea, y no printf
    }
    for(i=0;str[i]!='\0';i++){
        putchar(str[i]);
    }
    hexcol = DEFAULT;
    return i;
}

int print(char * str){
    return printColor(str, DEFAULT);
}


int printf(char *str, int first, int sec, int third) {
    char buffer[MAXBUFLEN], numStr[MAXBUFLEN];;
    int bufferIndex = 0;
    int numIndex = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '%' && str[i + 1] == 'd') {
            i++;
            if (numIndex == 0){
                intToString(first, numStr, MINLEN);
            }
            else if (numIndex == 1){
                intToString(sec, numStr, MINLEN);
            }
            else if (numIndex == 2){
                intToString(third, numStr, MINLEN);
            }
            
            for (int j = 0; numStr[j] != '\0'; ++j) {
                buffer[bufferIndex++] = numStr[j];
            }
            numIndex++;
        } else {
            buffer[bufferIndex++] = str[i];
        }
    }
    buffer[bufferIndex] = '\0';
    return print(buffer);
}

int scanf(char * buffer, int size){
    
    int fd = sysGetReadFileDescriptor(sysGetCurrentPid());
    if(size == 0 || fd == -1) {
        return 0;
    }
    
    unsigned char read = 0;
    int readSize = 0, printedSize = 0;
    while(read != '\n'){
        ctrlFlag = sysCtrlPressed();
        read = getchar();
        if(!readSizeFlag)
            continue;
        
        if(ctrlFlag && fd == STDIN){
            if(read == 'i'){
                checkZoomFlag = incTextSize();
                if(checkZoomFlag){
                    print("   Maximum Size Reached.");
                    sysHideCursor();
                    sysPrintCursor();
                    sysSleep(0, 15);
                    for(int i=0; i<strlen("   Maximum Size Reached."); i++){
                        putchar('\b');
                    }
                    sysShowCursor();
                    sysPrintCursor();
                }
            }
            else if(read == 'o'){
                checkZoomFlag = decTextSize();
                if(checkZoomFlag){
                    print("   Minimum Size Reached.");
                    sysHideCursor();
                    sysPrintCursor();
                    sysSleep(0,15);
                    for(int i=0; i<strlen("   Minimum Size Reached."); i++){
                        putchar('\b');
                    }
                    sysShowCursor();
                    sysPrintCursor();
                }
            }
        }
        else{
            if(read=='\n'){
                buffer[readSize] = 0;
                if (readSize > 0) strcpy(inputs[inputIndex++ % MAX_INPUTS_STORE], buffer);
                if (fd == STDIN) putchar(read);  // Newline
            }
            else if(read=='\b' && readSize!=0){
                if(readSize>=printedSize){
                    readSize--;
                    buffer[readSize]=0;
                }
                if (fd == STDIN) putchar(read);  // Backspace
                printedSize--;
            }
            else if (isVerticalArrow(read)) {
                if (read == sysUpArrowValue()) {
                    if (inputIndex > 0) {
                        inputIndex--;
                    }
                } else {
                    if (inputIndex < MAX_INPUTS_STORE) {
                        inputIndex++;
                    }
                }
                strcpy(buffer, inputs[inputIndex % MAX_INPUTS_STORE]);
                int commandLen = strlen(buffer);
                if (fd == STDIN) {
                    for(int i=0; i<printedSize; i++)
                        putchar('\b');
                }
                printedSize = commandLen;
                readSize = commandLen;
                print(buffer);
            }
            else if(isPrintable(read)){       // Printable Character
                if(readSize!=size)
                    buffer[readSize++] = read;
                if (fd == STDIN) putchar(read);
                printedSize++;
            }
        }
    }
    return readSize;
}

static int isPrintable(unsigned char c){
    return (c>=' ' && c<='~');
}

static int isVerticalArrow(unsigned char c) {
    return c == sysUpArrowValue() || c == sysDownArrowValue();
}