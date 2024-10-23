#include <string.h>
#include <stdint.h>

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
    char *ptr = str;
    char *low;
    static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
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

int strcmp(const char * str1, const char * str2){
    int i,j;
    i=j=0;
    while(str1[i]!='\0' && (str1[i] == str2[j])){
        i++;
        j++;
    }
    return str1[i] - str2[j];
}

void itoa64(uint64_t value, char* str, int base) {
    char* ptr = str;
    char* ptr1 = str;
    char tmp_char;
    uint64_t tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEF"[tmp_value - value * base];
    } while (value);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

char* strconcat(char* dest, const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    strcpy(dest, str1);
    strcpy(dest+len1, str2);
    return dest;
}