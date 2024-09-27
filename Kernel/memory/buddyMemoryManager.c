#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
}MemoryManagerCDT;

int get_max_size(size_t size, size_t block_size){

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

    mm->next = (BuddyNode *)(mm->root + sizeof(BuddyNode));
    return mm;
}

void* malloc_mm(MemoryManagerADT mm, size_t size) {
    
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    
}

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm) {
    
}