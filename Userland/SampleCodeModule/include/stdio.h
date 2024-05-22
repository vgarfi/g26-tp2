#ifndef __STDIO_H_
#define __STDIO_H_

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
 * Receives a string as a parameter 
 * Writes the string on STDOUT
 * Returns the length of the written string
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