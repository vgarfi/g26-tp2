#include <stdio.h>
#include <stdlib.h>

typedef struct TQueueCDT* TQueueADT;

TQueueADT createQueue();

void enqueue(TQueueADT queue, void* value);

void* dequeue(TQueueADT queue);

void* dequeue_value(TQueueADT queue, void* value);

void* peek(TQueueADT queue);

int is_empty(TQueueADT queue);