#include "include/string.h"
#include "include/stdio.h"

static void toLower(char * str);

int strlen(const char * str){
    int size;
    for(size=0; str[size]!='\0'; size++);
    return size;
}

int strcmp(const char * str1, const char * str2){
    if (str1 == 0 || str2 == 0) return 0;
    int i,j;
    i=j=0;
    while(str1[i]!='\0' && (str1[i] == str2[j])){
        i++;
        j++;
    }
    return str1[i] - str2[j];
}

char * strcpy(char *dest, const char *src){
    int len=strlen(src), i;
    for(i=0; i<len; i++){
        dest[i]=src[i];
    }
    dest[i]='\0';
    return dest;
}

int strcasecmp(const char * str1, const char * str2){
    int len1 = strlen(str1), len2=strlen(str2);
    char s1[len1], s2[len2];
    strcpy(s1,str1);
    strcpy(s2, str2);
    toLower(s1);
    toLower(s2);
    return strcmp(s1,s2);
}


/**
 * Turns str received as a parameter to lowerCase
*/
static void toLower(char * str){
    for(int i=0; str[i]!='\0'; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i]+=LOWERCASEDIFF;
        }
    }
}
int atoi(char *str) {
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