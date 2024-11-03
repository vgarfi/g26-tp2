#ifndef __STRING_H_
#define __STRING_H_

#define LOWERCASEDIFF 32

/**
 * Returns length of the received string
*/
int strlen(const char * str);

/**
 * Receives two strings and compares them.
 * Returns a negative integer if str1 is before str2
 * Returns positive integer if str1 is after str2
 * Returns 0 if both strings are the same
 * 
 * | | | Case sensitive function | | |  
*/
int strcmp(const char * str1, const char * str2);

/**
 * Receives two strings and compares them
 * Similar to strcmp but ignores uppercase
 * chars.
*/
int strcasecmp(const char * str1, const char * str2);

/**
 * Receives two strings as parameters
 * Copies the string in src to dest.
 * Returns a pointer to dest.
*/
char * strcpy(char *dest, const char *src);

/**
 * Recieves a numeric value, a buffer and the base
 * Transforms the number to its ASCII value and places it into the buffer
*/
void itoa(int value, char* str, int base);

/**
 * Recieves a stirng containing a number
 * Transforms the string to its numeric value and
 * Returns the numeric value
*/
int atoi(char *str);

/**
 * Recieves a char and a string
 * Returns 1 if the string contains the character.
*/
int contains(char* str, char c);


/**
 * Recieves a string, a char delimiter and two buffers
 * Splits the string into two substrings separated by the delimiter
*/
int strsplit(const char* str, char delimiter, char* res1, char* res2);
#endif