#include <structures/listADT.h>
#include <memory/memoryManagerADT.h>
#include <string.h>

#define FALSE       0
#define TRUE        1

extern MemoryManagerADT memory_manager;

typedef struct TNode {
    void* data;
    struct TNode* next;
} TNode;

typedef struct TListCDT {
    TNode* head;
    int (*cmpFunc)(const void*, const void*);
} TListCDT;

TListADT create_list(int (*cmpFunc)(const void*, const void*)) {
    TListADT newList = (TListADT) malloc_mm(memory_manager, sizeof(TListCDT));
    if (newList == NULL) {
        return NULL;
    }
    newList->head = NULL;
    newList->cmpFunc = cmpFunc;
    return newList;
}

char insert_element(TListADT list, void* element) {
    TNode* newNode = (TNode*) malloc_mm(memory_manager, sizeof(TNode));
    if (newNode == NULL) {
        return FALSE; 
    }
    newNode->data = element;
    newNode->next = NULL;

    if (list->head != NULL && list->cmpFunc(element, list->head->data) == 0) {
        free_mm(memory_manager, newNode);
        return FALSE;
    }

    if (list->head == NULL || list->cmpFunc(element, list->head->data) <= 0) {
        newNode->next = list->head;
        list->head = newNode;
        return TRUE;
    }

    TNode* prev = NULL;
    TNode* current = list->head;
    while (current != NULL && list->cmpFunc(element, current->data) >= 0) {
        if (list->cmpFunc(element, list->head->data) == 0) {
            free_mm(memory_manager, newNode);
            return FALSE;
        }
        prev = current;
        current = current->next;
    }

    newNode->next = current;
    prev->next = newNode;

    return TRUE;
}

char remove_element(TListADT list, void* element) {
    if (list == NULL || list->head == NULL) {
        return FALSE;
    }

    TNode* current = list->head;
    TNode* prev = NULL;

    while (current != NULL && list->cmpFunc(element, current->data) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return FALSE;
    }

    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    free_mm(memory_manager, current);
    return 1;
}

void* get_element(TListADT list, void* element) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    TNode* current = list->head;

    while (current != NULL && list->cmpFunc(element, current->data) > 0) {
        current = current->next;
    }

    if (current != NULL && list->cmpFunc(element, current->data) == 0) {
        return current->data;
    }

    return NULL;
}

void destroy_list(TListADT list) {
    if (list == NULL) {
        return;
    }

    TNode* current = list->head;
    TNode* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free_mm(memory_manager, current);
        current = nextNode;
    }

    free_mm(memory_manager, list);
    list = NULL;
}