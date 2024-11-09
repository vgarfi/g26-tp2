#ifndef LIB_H
#define LIB_H

#include <stdint.h>

/**
 * @brief Sets a block of memory with a specified value.
 *
 * @param destination Pointer to the block of memory to fill.
 * @param character The value to be set.
 * @param length Number of bytes to be set to the value.
 * @return A pointer to the memory area destination.
 */
void * memset(void * destination, int32_t character, uint64_t length);

/**
 * @brief Copies a block of memory from one location to another.
 *
 * @param destination Pointer to the destination array where the content is to be copied.
 * @param source Pointer to the source of data to be copied.
 * @param length Number of bytes to copy.
 * @return A pointer to the destination.
 */
void * memcpy(void * destination, const void * source, uint64_t length);

/**
 * @brief Saves the current state of the registers.
 */
void save_regs(void);

/**
 * @brief Prints the saved state of the registers.
 *
 * @return 0 on success, -1 on failure.
 */
int reg_printing(void);

/**
 * @brief Stops the currently running process.
 */
void stop_running(void);

/**
 * @brief Sends an end-of-file signal.
 */
void send_end_of_file(void);

#endif