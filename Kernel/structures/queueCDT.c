#include "../include/structures/queueADT.h"
#include "../kernel.c"                      // TODO prguntar la correctitud de esto


TQueueCDT createQueue() {
    TQueueCDT queue = (TQueueCDT)malloc_mm(memory_manager, sizeof(TQueueADT));
    queue->first = queue->last = NULL;
    return queue;
}

void enqueue(TQueueCDT queue, void* value) {
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

void* dequeue(TQueueCDT queue) {
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

int isEmpty(TQueueCDT queue) {
    return queue->first == NULL;
}