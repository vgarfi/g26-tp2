#include "../include/structures/queueADT.h"
#include "../kernel.c"                      // TODO prguntar la correctitud de esto


typedef struct TQueueNode {
    void* data;            
    struct TQueueNode* next;    
} TQueueNode;

typedef struct TQueueCDT {
    TQueueNode* first;
    TQueueNode* last;
} TQueueCDT;


TQueueADT createQueue() {
    TQueueADT queue = (TQueueADT)malloc_mm(memory_manager, sizeof(TQueueCDT));
    queue->first = queue->last = NULL;
    return queue;
}

void enqueue(TQueueADT queue, void* value) {
    TQueueNode* newNode = (TQueueNode*)malloc_mm(memory_manager, sizeof(TQueueNode));
    newNode->data = value;
    newNode->next = NULL;

    if (queue->last == NULL) {
        queue->first = queue->last = newNode;
        return;
    }

    queue->last->next = newNode;
    queue->last = newNode;
}

void* dequeue(TQueueADT queue) {
    if (queue->first == NULL) {
        return NULL;
    }

    TQueueNode* temp = queue->first;
    void* data = temp->data;
    queue->first = queue->first->next;

    if (queue->first == NULL) {
        queue->last = NULL;
    }

    free_mm(memory_manager,temp);
    return data;
}

int isEmpty(TQueueADT queue) {
    return queue->first == NULL;
}

void* peek(TQueueADT queue){
    return (queue->first == NULL)? NULL : queue->first->data;
}