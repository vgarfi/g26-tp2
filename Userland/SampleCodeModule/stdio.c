#include "include/stdio.h"
#include "include/syscalls.h"

unsigned char getchar(void){
    unsigned char read=0;
    readScreen(STDIN, &read, 1);
    return read;
}

int putchar(unsigned char c){
    writeScreen(STDOUT, &c, 1);
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
        if(read=='\n'){
            buffer[readSize]=0;
            putchar(read);  // Function to print newLine
        }
        else if(read=='\b' && readSize!=0){
            readSize--;
            buffer[readSize]=0;
            putchar(read);  // Function to print backspace
        }
        else{       // Is a character (May be modified due to game in the future)
            buffer[readSize++]=read;
            putchar(read);
        }
    }
    return readSize;
}
