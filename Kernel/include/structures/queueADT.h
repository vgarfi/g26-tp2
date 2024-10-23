#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TQueueCDT* TQueueADT;

TQueueADT createQueue();

void enqueue(TQueueADT queue, void* value);

void* dequeue(TQueueADT queue);

void* dequeue_value(TQueueADT queue, void* value);

void* peek(TQueueADT queue);

int count_occurrences(TQueueADT queue, void* value);

int is_empty(TQueueADT queue);

void dump(TQueueADT queue);
void destroy_queue(TQueueADT queue);

#endif