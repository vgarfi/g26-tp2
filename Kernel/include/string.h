#ifndef __STRING_H_
#define __STRING_H_

#include <stdint.h>

/**
 * @brief Calculates the length of a string.
 *
 * @param str The string whose length is to be calculated.
 * @return The length of the string.
 */
int strlen(const char *str);

/**
 * @brief Copies a string from source to destination.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @return A pointer to the destination string.
 */
char * strcpy(char *dest, const char *src);

/**
 * @brief Converts an integer value to a null-terminated string using the specified base.
 *
 * @param value The integer value to convert.
 * @param str The buffer to store the resulting string.
 * @param base The base for the conversion (e.g., 10 for decimal, 16 for hexadecimal).
 */
void itoa(int value, char* str, int base);

/**
 * @brief Converts a 64-bit integer value to a null-terminated string using the specified base.
 *
 * @param value The 64-bit integer value to convert.
 * @param str The buffer to store the resulting string.
 * @param base The base for the conversion (e.g., 10 for decimal, 16 for hexadecimal).
 */
void itoa64(uint64_t value, char* str, int base);

/**
 * @brief Compares two strings.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return An integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater than str2.
 */
int strcmp(const char * str1, const char * str2);

/**
 * @brief Concatenates two strings into the destination buffer.
 *
 * @param dest The destination buffer.
 * @param str1 The first string.
 * @param str2 The second string.
 * @return A pointer to the destination string.
 */
char* strconcat(char* dest, const char* str1, const char* str2);

/**
 * @brief Converts a string to an integer.
 *
 * @param str The string to convert.
 * @return The converted integer value.
 */
int64_t satoi(char *str);

#endif