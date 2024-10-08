#include <string.h>

int strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char * strcpy(char *dest, const char *src){
    int len=strlen(src), i;
    for(i=0; i<len; i++){
        dest[i]=src[i];
    }
    dest[i]='\0';
    return dest;
}