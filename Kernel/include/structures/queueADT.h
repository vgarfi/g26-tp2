/**
 * @file queueADT.h
 * @brief Definition of the Queue Abstract Data Type (ADT) and related functions.
 */

#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @typedef TQueueADT
 * @brief A pointer to a concrete structure representing the queue.
 */
typedef struct TQueueCDT* TQueueADT;

/**
 * @brief Creates a new queue.
 *
 * @return A new initialized TQueueADT.
 */
TQueueADT create_queue();

/**
 * @brief Enqueues a value into the queue.
 *
 * @param queue The queue.
 * @param value The value to enqueue.
 */
void enqueue(TQueueADT queue, void* value);

/**
 * @brief Dequeues a value from the queue.
 *
 * @param queue The queue.
 * @return A pointer to the dequeued value, or NULL if the queue is empty.
 */
void* dequeue(TQueueADT queue);

/**
 * @brief Dequeues a specific value from the queue.
 *
 * @param queue The queue.
 * @param value The value to dequeue.
 * @return A pointer to the dequeued value, or NULL if the value is not found.
 */
void* dequeue_value(TQueueADT queue, void* value);

/**
 * @brief Peeks at the front value of the queue without dequeuing it.
 *
 * @param queue The queue.
 * @return A pointer to the front value, or NULL if the queue is empty.
 */
void* peek(TQueueADT queue);

/**
 * @brief Counts the occurrences of a value in the queue.
 *
 * @param queue The queue.
 * @param value The value to count.
 * @return The number of occurrences of the value in the queue.
 */
int count_occurrences(TQueueADT queue, void* value);

/**
 * @brief Checks if the queue is empty.
 *
 * @param queue The queue.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int is_empty(TQueueADT queue);

/**
 * @brief Destroys the queue and frees all associated memory.
 *
 * @param queue The queue to destroy.
 */
void destroy_queue(TQueueADT queue);

#endif