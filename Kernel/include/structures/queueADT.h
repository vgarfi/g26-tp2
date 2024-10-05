#include <stdio.h>
#include <stdlib.h>

typedef struct TQueueCDT* TQueueADT;

TQueueADT createQueue();

void enqueue(TQueueADT queue, void* value);

void* dequeue(TQueueADT queue);

void* peek(TQueueADT queue);

int isEmpty(TQueueADT queue);