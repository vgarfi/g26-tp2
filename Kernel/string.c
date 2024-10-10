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


void itoa(int value, char* str, int base) {
    char *rc;
    char *ptr;
    char *low;
    static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    rc = ptr = str;
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }
    low = ptr;
    do {
        *ptr++ = digits[value % base];
        value /= base;
    } while (value);
    *ptr-- = '\0';
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
}