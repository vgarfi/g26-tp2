// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/structures/queueADT.h"
#include <kernelManagement.h>
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


TQueueADT create_queue() {
    TQueueADT queue = (TQueueADT)malloc_mm(memory_manager, sizeof(TQueueCDT));
    if (queue == NULL) {
        return NULL;
    }
    queue->first = queue->last = NULL;
    return queue;
}

void enqueue(TQueueADT queue, void* value) {
    if (queue == NULL) {
        return;
    }
    TQueueNode* new_node = (TQueueNode*)malloc_mm(memory_manager, sizeof(TQueueNode));
    
    if (new_node == NULL) {
        return;
    }
    
    new_node->value = value;
    new_node->next = NULL;

    if (queue->last == NULL) {
        queue->first = queue->last = new_node;
        return;
    }

    queue->last->next = new_node;
    queue->last = new_node;
}

void* dequeue(TQueueADT queue) {
    if (queue == NULL || queue->first == NULL) {
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
    if (queue == NULL) {
        return NULL;
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
        return 0;
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
    TQueueNode* next_node;

    while (current != NULL) {
        next_node = current->next;
        free_mm(memory_manager, current);
        current = next_node;
    }

    free_mm(memory_manager, queue);
    return;
}