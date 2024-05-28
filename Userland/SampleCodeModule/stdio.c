#include "include/stdio.h"
#include "include/syscalls.h"
#include "include/colors.h"
#include "include/string.h"
#include "include/lib.h"

#define MAXBUFLEN 100
#define MINLEN 2

/**
 * readSizeFlag is used as a way of identifying whether
 * getChar returned with no value read because of timeout
 * or not
*/
static int readSizeFlag=0;

static uint64_t hexcol=DEFAULT;   // default shell color

static int isPrintable(unsigned char c);

unsigned char getchar(void){
    unsigned char read=0;
    readSizeFlag=readScreen(STDIN, &read, 1);
    return read;
}

int putchar(unsigned char c){
    writeScreen(STDOUT, &c, 1, hexcol);
    return c;
}

int printColor(char* str, uint64_t hexColor){
    hexcol=hexColor;
    int i;
    for(i=0;str[i]!='\0';i++){
        putchar(str[i]);
    }
    hexcol=DEFAULT;
    return i;
}

int print(char * str){
    printColor(str, DEFAULT);
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
    if(size==0)
        return 0;
    unsigned char read=0;
    int readSize=0, printedSize=0;
    while(read!='\n'){
        read=getchar();
        if(!readSizeFlag)
            continue;

        if(read=='\n'){
            // TODO: check if this is necessary
            /**
             * if(readSize==size)
             *  buffer[--readSize]=0;
             * else
             *  buffer[readSize]=0;
            */
            buffer[readSize]=0;
            putchar(read);  // Newline
        }
        else if(read=='\b' && readSize!=0){
            if(readSize>=printedSize)
                readSize--;
                buffer[readSize]=0;
            putchar(read);  // Backspace
            printedSize--;
        }
        else if(isPrintable(read)){       // Printable Character
            if(readSize!=size)
                buffer[readSize++]=read;
            putchar(read);
            printedSize++;
        }
    }
    return readSize;
}

static int isPrintable(unsigned char c){
    return (c>=' ' && c<='~');
}