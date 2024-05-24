#ifndef __STDIO_H_
#define __STDIO_H_

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/**
 * Reads STDIN and returns the next char in it.
 * If STDIN buffer is empty, waits for input and returns it
*/
unsigned char getchar(void);

/**
 * Receives a char and prints it on STDOUT
 * Returns the character written.
*/
int putchar(unsigned char c);

/**
 * Receives a string and a hexcode as parameters
 * Writes the string on STDOUT in the received hexColor
 * Returns the length of the written string
*/

int printColor(char* str, uint64_t hexColor);

/**
 * Receives a string as a parameter 
 * Similar to printColor but uses DEFAULT as hexColor (defined in color.h)
*/

int print(char * str);

/**
 * Receives a buffer and size as parameters
 * Reads STDIN and fills the buffer with its content
 * until size is reached or '\n' is read.
 * Returns the number of chars read.
*/
int scanf(char * buffer, int size);



#endif