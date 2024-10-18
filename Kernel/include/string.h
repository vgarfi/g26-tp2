#ifndef __STRING_H_
#define __STRING_H_

#include <stdint.h>

int strlen(const char *str);
char * strcpy(char *dest, const char *src);
void itoa(int value, char* str, int base);
void itoa64(uint64_t value, char* str, int base);
int strcmp(const char * str1, const char * str2);

#endif