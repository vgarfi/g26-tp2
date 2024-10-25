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
    if (queue == NULL) {
        vdPrint("\nERROR al create queue", 0x00FF0000);
        return NULL;
    }
    queue->first = queue->last = NULL;
    return queue;
}

void enqueue(TQueueADT queue, void* value) {
    if (queue == NULL) {
        return;
    }
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
    if (queue == NULL || queue->first == NULL) {
        return;
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
    if (queue == NULL) {
        return;
    }
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
    if (queue == NULL) {
        return;
    }
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
    return queue == NULL || queue->first == NULL;
}

void* peek(TQueueADT queue){
    return (queue == NULL || queue->first == NULL)? NULL : queue->first->value;
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
    return;
}


void dump(TQueueADT queue){
    if (queue == NULL) {
        return;
    }
    TQueueNode* current = queue->first;
    while (current != NULL) {
        uint8_t pid = (uint8_t)current->value;
        char buffer[10];
        itoa(pid, buffer, 10);
        vdPrint(buffer, 0x00FFFFFF);
        vdPrint(" - ", 0x00FFFFFF);
        current = current->next;
    }
}