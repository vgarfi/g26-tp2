#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "memoryManagerADT.h"

typedef struct BuddyNode {
    BuddyNode * left;
    BuddyNode * right;
    char free; 
} BuddyNode;

typedef struct MemoryManagerCDT {
    void* base;
    size_t total_size;
    size_t block_size;
    BuddyNode * root;
    BuddyNode * next;
    void* free_space;
}MemoryManagerCDT;

int get_max_size(size_t size, size_t block_size){
    size_t max_size = block_size;
    while (max_size < size) {
        max_size *= 2;
    }
    return max_size;
}

int get_height(size_t size, size_t block_size){
    return log2(size/block_size);
}

int get_qty_nodes(int height){
    return pow(2, height+1) - 1;
}

MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    mm->total_size = get_max_size(size, block_size);
    mm->base = base
                + sizeof(MemoryManagerCDT)
                + sizeof(BuddyNode)*get_qty_nodes(get_height(mm->total_size, block_size));

    mm->block_size = block_size;

    mm->root = (BuddyNode *)(base + sizeof(MemoryManagerCDT));
    mm->root->free = 1;
    mm->root->left = NULL;
    mm->root->right = NULL;
    mm->free_space = mm->root + sizeof(BuddyNode); 

    mm->next = (BuddyNode *)(mm->root + sizeof(BuddyNode));
    return mm;
}

BuddyNode* get_free_node(BuddyNode* current, size_t looked_size, size_t current_size, MemoryManagerADT mm) {
    if (current == NULL || !current->free) {
        return NULL;
    }

    if (current_size == looked_size) {
        current->free = 0;
        return current;
    }

    // Si el nodo no tiene hijos, debemos dividirlo
    if (current->left == NULL && current->right == NULL) {
        size_t half_size = current_size / 2;

        BuddyNode* left_child = (BuddyNode*)mm->free_space;
        mm->free_space += sizeof(BuddyNode);
        BuddyNode* right_child = (BuddyNode*)mm->free_space;
        mm->free_space += sizeof(BuddyNode);

        left_child->free = 1;
        left_child->left = NULL;
        left_child->right = NULL;

        right_child->free = 1;
        right_child->left = NULL;
        right_child->right = NULL;

        current->left = left_child;
        current->right = right_child;
    }

    BuddyNode* result = get_free_node(current->left, looked_size, current_size / 2, mm);
    if (result != NULL) {
        return result;
    }

    return get_free_node(current->right, looked_size, current_size / 2, mm);
}

size_t get_block_looked_size(size_t real_size) {
    if (real_size <= 1) {
        return 1;
    }

    size_t power_of_two = 1;
    while (power_of_two < real_size) {
        power_of_two *= 2;
    }
    return power_of_two;
}

void* malloc_mm(MemoryManagerADT mm, size_t size) {
    if (size == 0 || size > mm->total_size) {
        return NULL;
    }

    size_t block_looked_size = get_block_looked_size(size);
    if(block_looked_size < mm->block_size){
        block_looked_size = mm->block_size;
    }

    BuddyNode* node = get_free_node(mm->root, block_looked_size, mm->total_size, mm);
    if(node == NULL)
        return node;
    
    node->free = 0;
    return (void*)node;
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    
}

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm) {
    
}