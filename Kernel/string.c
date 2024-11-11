#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <videoDriver.h>

int strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char * strcpy(char *dest, const char *src){
    int len = strlen(src), i;
    
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
    if(str1 == NULL || str2 == NULL){
        return 0;
    }
    int i = 0;
    while(str1[i]!='\0' && (str1[i] == str2[i])){
        i++;
    }
    return str1[i] - str2[i];
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
    strcpy(dest, str1);
    strcpy(dest+len1, str2);
    return dest;
}

int64_t satoi(char *str) {
  uint64_t i = 0;
  int64_t res = 0;
  int8_t sign = 1;

  if (!str)
    return 0;

  if (str[i] == '-') {
    i++;
    sign = -1;
  }

  for (; str[i] != '\0'; ++i) {
    if (str[i] < '0' || str[i] > '9')
      return 0;
    res = res * 10 + str[i] - '0';
  }

  return res * sign;
}