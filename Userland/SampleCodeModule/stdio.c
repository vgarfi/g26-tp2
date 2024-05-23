#include "include/stdio.h"
#include "include/syscalls.h"

/**
 * readSizeFlag is used as a way of identifying whether
 * getChar returned with no value read because of timeout
 * or not
*/
static int readSizeFlag=0;

static int isPrintable(unsigned char c);

unsigned char getchar(void){
    unsigned char read=0;
    readSizeFlag=readScreen(STDIN, &read, 1);
    return read;
}

int putchar(unsigned char c){
    writeScreen(STDOUT, &c, 1, (uint64_t)0x00FFFFFF);
    return c;
}

int print(char * str){
    int i;
    for(i=0;str[i]!='\0';i++){
        putchar(str[i]);
    }
    return i;
}

int scanf(char * buffer, int size){
    if(size==0)
        return 0;
    unsigned char read=0;
    int readSize=0;
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
            readSize--;
            buffer[readSize]=0;
            putchar(read);  // Backspace
        }
        else if(isPrintable(read)){       // Printable Character
            if(readSize!=size)
                buffer[readSize++]=read;
            putchar(read);
        }
    }
    return readSize;
}

static int isPrintable(unsigned char c){
    return (c>=' ' && c<='~');
}