/**
 * @file testUtil.h
 * @brief Definition of utility functions for testing.
 */

#ifndef __TEST_UTIL_H__
#define __TEST_UTIL_H__

#include <stdint.h>

/**
 * @brief Gets an unsigned integer.
 *
 * @return The unsigned integer.
 */
uint32_t GetUint(void);

/**
 * @brief Gets a uniform random number up to a specified maximum.
 *
 * @param max The maximum value.
 * @return The uniform random number.
 */
uint32_t GetUniform(uint32_t max);

/**
 * @brief Checks if a memory region contains a specified value.
 *
 * @param start The start of the memory region.
 * @param value The value to check for.
 * @param size The size of the memory region.
 * @return 1 if the memory region contains the value, 0 otherwise.
 */
uint8_t memcheck(void *start, uint8_t value, uint32_t size);

/**
 * @brief Converts a string to an integer.
 *
 * @param str The string to convert.
 * @return The converted integer.
 */
int64_t satoi(char *str);

/**
 * @brief Performs a busy wait for a specified duration.
 *
 * @param n The duration of the busy wait.
 */
void bussyWait(uint64_t n);

/**
 * @brief Executes an endless loop.
 */
void endlessLoop(void);

/**
 * @brief Executes an endless loop with periodic printing.
 *
 * @param wait The wait time between prints.
 */
void endlessLoopPrint(uint64_t wait);

#endif