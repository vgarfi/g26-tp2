#include "../include/structures/queueADT.h"
#include <kernelManagement.h>
#include <videoDriver.h>
#include <scheduler/scheduler.h>


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

    void* node_value = current->value;
    free_mm(memory_manager, current);

	return node_value;
}

int count_occurrences(TQueueADT queue, void* value) {
    int count = 0;
    TQueueNode* current = queue->first;

    while (current != NULL) {
        if (current->value == value) {
            count++;
        }
        current = current->next;
    }

    return count;
}

int is_empty(TQueueADT queue) {
    return queue->first == NULL;
}

void* peek(TQueueADT queue){
    return (queue->first == NULL)? NULL : queue->first->value;
}

void destroy_queue(TQueueADT queue) {
    if (queue == NULL) {
        return;
    }

    TQueueNode* current = queue->first;
    TQueueNode* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free_mm(memory_manager, current);
        current = nextNode;
    }

    free_mm(memory_manager, queue);
}

/*
void dump(TQueueADT queue){
    TQueueNode* current = queue->first;
    while (current != NULL) {
        TPCB* pcb = (TPCB*)current->value;
        vdPrint(pcb->name, 0x00FFFFFF);
        vdPrint(" - ", 0x00FFFFFF);
        current = current->next;
    }
}
*/