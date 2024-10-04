#include <stdio.h>
#include <stdlib.h>

typedef struct TQueueNode {
    void* data;            
    struct TQueueNode* next;    
} TQueueNode;

typedef struct TQueueADT {
    TQueueNode* first;
    TQueueNode* last;
} TQueueADT;

typedef TQueueADT* TQueueCDT;

TQueueCDT createQueue();

void enqueue(TQueueCDT queue, void* value);

void* dequeue(TQueueCDT queue);

void* peek(TQueueCDT queue);

int isEmpty(TQueueCDT queue);