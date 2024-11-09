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
    int (*cmp_func)(const void*, const void*);
} TListCDT;

TListADT create_list(int (*cmp_func)(const void*, const void*)) {
    TListADT new_list = (TListADT) malloc_mm(memory_manager, sizeof(TListCDT));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->cmp_func = cmp_func;
    return new_list;
}

char insert_element(TListADT list, void* element) {
    TNode* new_node = (TNode*) malloc_mm(memory_manager, sizeof(TNode));
    if (new_node == NULL) {
        return FALSE; 
    }
    new_node->data = element;
    new_node->next = NULL;

    if (list->head != NULL && list->cmp_func(element, list->head->data) == 0) {
        free_mm(memory_manager, new_node);
        return FALSE;
    }

    if (list->head == NULL || list->cmp_func(element, list->head->data) <= 0) {
        new_node->next = list->head;
        list->head = new_node;
        return TRUE;
    }

    TNode* prev = NULL;
    TNode* current = list->head;
    while (current != NULL && list->cmp_func(element, current->data) >= 0) {
        prev = current;
        current = current->next;
    }

    new_node->next = current;
    prev->next = new_node;

    return TRUE;
}

char remove_element(TListADT list, void* element) {
    if (list == NULL || list->head == NULL) {
        return FALSE;
    }

    TNode* current = list->head;
    TNode* prev = NULL;

    while (current != NULL && list->cmp_func(element, current->data) != 0) {
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

    while (current != NULL && list->cmp_func(element, current->data) > 0) {
        current = current->next;
    }

    if (current != NULL && list->cmp_func(element, current->data) == 0) {
        return current->data;
    }
    return NULL;
}

void destroy_list(TListADT list) {
    if (list == NULL) {
        return;
    }

    TNode* current = list->head;
    TNode* next_node;

    while (current != NULL) {
        next_node = current->next;
        free_mm(memory_manager, current);
        current = next_node;
    }

    free_mm(memory_manager, list);
    list = NULL;
}