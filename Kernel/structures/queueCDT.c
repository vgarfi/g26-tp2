#include "../include/structures/queueADT.h"
#include <kernel.h>                      // TODO prguntar la correctitud de esto

extern MemoryManagerADT memory_manager;

typedef struct TQueueNode {
    void* value;            
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
    newNode->value = value;
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
    void* value = temp->value;
    queue->first = queue->first->next;

    if (queue->first == NULL) {
        queue->last = NULL;
    }

    free_mm(memory_manager,temp);
    return value;
}
void* dequeue_value(TQueueADT queue, void* value) {
    TQueueNode * current = queue->first;
	TQueueNode * previous = NULL;
	while (current != NULL && current->value != value) {
		previous = current;
		current = current->next;
	}

	if (current == NULL) {
		return NULL;
	}

	if (previous == NULL) {
		queue->first = current->next;
	} else {
		previous->next = current->next;
	}

	if (current == queue->last) {
		queue->last = previous;
	}

	return current->value;
}

int is_empty(TQueueADT queue) {
    return queue->first == NULL;
}

void* peek(TQueueADT queue){
    return (queue->first == NULL)? NULL : queue->first->value;
}