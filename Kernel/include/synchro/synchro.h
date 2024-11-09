/**
 * @file synchro.h
 * @brief Definition of synchronization primitives and related functions.
 */

#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdint.h>
#include <structures/queueADT.h>

/**
 * @struct TSemaphore
 * @brief Structure representing a semaphore.
 */
typedef struct TSemaphore {
    char* name;                  /**< Name of the semaphore */
    uint64_t value;              /**< Current value of the semaphore */
    uint8_t lock;                /**< Lock state of the semaphore */
    TQueueADT waiting_processes; /**< Queue of processes waiting on the semaphore */
} TSemaphore;

/**
 * @brief Initializes the synchronization system.
 *
 * @return 1 on success, 0 on failure.
 */
char initialize_synchro(void);

/**
 * @brief Creates a new semaphore.
 *
 * @param name The name of the semaphore.
 * @param initial_value The initial value of the semaphore.
 * @return A pointer to the created semaphore, or NULL on failure.
 */
TSemaphore* create_sem(char* name, uint64_t initial_value);

/**
 * @brief Gets a semaphore by its name.
 *
 * @param name The name of the semaphore.
 * @return A pointer to the semaphore, or NULL if not found.
 */
TSemaphore* get_sem(char* name);

/**
 * @brief Waits (decrements) a semaphore.
 *
 * @param name The name of the semaphore.
 */
void wait_sem(char* name);

/**
 * @brief Posts (increments) a semaphore.
 *
 * @param name The name of the semaphore.
 */
void post_sem(char* name);

/**
 * @brief Deletes a semaphore.
 *
 * @param name The name of the semaphore.
 */
void delete_sem(char* name);

#endif