#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "memoryManagerADT.h"

#define FREE                1
#define NOT_FREE            0

typedef struct BuddyNode BuddyNode;

BuddyNode* find_parent(BuddyNode* root, BuddyNode* node);
void split_node(BuddyNode* current, int remaining_nodes);
size_t get_block_looked_size(size_t real_size);

struct BuddyNode {
    BuddyNode * left;
    BuddyNode * right;
    char free; 
};

typedef struct MemoryManagerCDT {
    void* base;
    size_t total_size;
    size_t block_size;
    BuddyNode * root;
}MemoryManagerCDT;

int get_max_size(size_t size, size_t block_size){
    size_t max_size = block_size;
    while (max_size * 2 < size) {
        max_size *= 2;
    }
    return max_size;
}

int get_height(size_t size, size_t block_size){
    if (block_size == 0) {
        printf("Error: block_size es 0\n");
        return -1; // o un valor adecuado de error
    }
    return log2(size/block_size);
}

int get_qty_nodes(int height){
    return (int)(pow(2, height+1) - 1);
}

MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    
    mm->block_size = get_block_looked_size(block_size);

    mm->total_size = size - sizeof(MemoryManagerCDT) - sizeof(BuddyNode) * get_qty_nodes(get_height(size, block_size));
    
    mm->total_size = get_max_size(mm->total_size, block_size);

    mm->base = (void*)((char*)base + sizeof(MemoryManagerCDT) + sizeof(BuddyNode) * get_qty_nodes(get_height(mm->total_size, block_size)));

    mm->root = (BuddyNode*)((char*)base + sizeof(MemoryManagerCDT));
    mm->root->free = FREE;
    mm->root->left = NULL;
    mm->root->right = NULL;

    return mm;
}

void split_node(BuddyNode* current, int remaining_nodes) {  
    current->left = (BuddyNode*)((char*)current + sizeof(BuddyNode));
    current->right = (BuddyNode*)((char*)current->left + (remaining_nodes/2)*sizeof(BuddyNode));

    current->left->free = FREE;
    current->left->left = NULL;
    current->left->right = NULL;

    current->right->free = FREE;
    current->right->left = NULL;
    current->right->right = NULL;

    current->free = NOT_FREE;
}

BuddyNode* get_free_node(BuddyNode* current, size_t looked_size, size_t current_size,  int* offset, int remaining_nodes, int min_block_size) {
    if (current == NULL || current->free == NOT_FREE || current_size < min_block_size) {
        return NULL;
    }

    if (current_size == looked_size) {
        current->free = NOT_FREE;
        return current;
    }
    
    remaining_nodes--;

    // Si el nodo no tiene hijos, debemos dividirlo
    if (current->left == NULL && current->right == NULL) {
        split_node(current, remaining_nodes);
    }

    BuddyNode* result = get_free_node(current->left, looked_size, current_size / 2, offset, remaining_nodes/2, min_block_size);
    if (result != NULL) {
        return result;
    }

    *offset = *offset + current_size/2;
    return get_free_node(current->right, looked_size, current_size / 2, offset, remaining_nodes/2, min_block_size);
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

    int offset = 0;

    BuddyNode* node = get_free_node(mm->root, block_looked_size, mm->total_size, &offset, get_qty_nodes(get_height(mm->total_size, mm->block_size)), mm->block_size);
    if(node == NULL)
        return NULL;
    
    return (void*)((char*)mm->base + offset);
}

/*void merge_brother_buddies2(BuddyNode* current, BuddyNode* root) {
    if (current == NULL || current == root) {
        return;
    }

    BuddyNode* parent = find_parent(root, current);

    if (parent == NULL) {
        return;
    }

    BuddyNode* left = parent->left;
    BuddyNode* right = parent->right;

    if (left->free && right->free) {
        parent->free = FREE;
        parent->left = NULL;
        parent->right = NULL;

        merge_brother_buddies2(parent, root); // Por si también es necesario mergearlo a él también
    }
}*/

/*BuddyNode* find_parent(BuddyNode* root, BuddyNode* node) {
    if (root == NULL || root->left == NULL || root->right == NULL) {
        return NULL;
    }

    if (root->left == node || root->right == node) {
        return root;
    }

    BuddyNode* left_parent = find_parent(root->left, node);
    if (left_parent != NULL) {
        return left_parent;
    }

    return find_parent(root->right, node);
}*/


/*BuddyNode* find_buddy_node2(BuddyNode* current, void* base, void* ptr, size_t current_size, int* offset) {
    if (current == NULL) {
        return NULL;
    }

    if ((void*)((char*)base + *offset) == ptr) {
        return current;
    }


    BuddyNode* result = find_buddy_node2(current->left, base, ptr, current_size/2, offset);
    if (result != NULL) {
        return result;
    }

    *offset += current_size/2;
    return find_buddy_node2(current->right, base, ptr, current_size/2, offset);
}*/

BuddyNode* find_buddy_node(MemoryManagerADT mm, void* base, void*ptr){
    size_t offset = (char*)ptr - (char*)mm->base;

    int index = offset / mm->block_size;

    BuddyNode* node = (BuddyNode*)((char*)mm->root + index * sizeof(BuddyNode));
}

int get_remaining_nodes(BuddyNode* current, BuddyNode* root){
    int current_index = (current - root) / sizeof(BuddyNode);
    int height = 0;

    // Calcular la altura (0 para hojas, 1 para sus padres, etc.)
    while (current_index > 0) {
        current_index = (current_index - 1) / 2;
        height++;
    }

    return (1 << height) - 1; // 2^height - 1
}

void merge_brother_buddies(BuddyNode* current, BuddyNode* root) {
    if (current == NULL || root == NULL) {
        return;
    }

    int current_index = (current - root) / sizeof(BuddyNode);

    if (current_index == 0) {
        return;
    }

    int parent_index = (current_index - 1) / 2;
    BuddyNode* parent = root + parent_index; // se ajusta automaticamente por aritmetica de punteros

    BuddyNode* sibling;
    if (current_index % 2 == 0) {
        sibling = root + (current_index - 1);
    } else {
        int remaining_nodes = get_remaining_nodes(current, root);
        sibling = root + (current_index - 1) + (remaining_nodes/2);
    }

    if (sibling->free == FREE && current->free == FREE) {
        parent->free = FREE;
        parent->left = NULL;
        parent->right = NULL;

        merge_brother_buddies(parent, root);
    }
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    if (ptr == NULL || ptr < mm->base || ptr >= (mm->base + mm->total_size)) {
        return;
    }

    //int offset = 0;
    //BuddyNode* node = find_buddy_node(mm->root, mm->base, ptr, mm->total_size, &offset);
    BuddyNode* node = find_buddy_node(mm, mm->base, ptr);

    if (node == NULL) {
        return;
    }
        printf("Liberando nodo en dirección: %p\n", node);
    node->free = FREE;

    merge_brother_buddies(node, mm->root);
}

void calculate_diagnostic(MemoryDiagnostic* diagnostic, BuddyNode* node, size_t current_size, size_t block_size) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {

        if (node->free) {
            diagnostic->free_memory += current_size;
            diagnostic->free_blocks+= current_size/block_size;
        } else {
            diagnostic->used_memory += current_size;
            diagnostic->used_blocks += current_size/block_size;
        }
    } else {
        calculate_diagnostic(diagnostic, node->left, current_size / 2, block_size);
        calculate_diagnostic(diagnostic, node->right, current_size / 2, block_size);
    }
}

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm) {
    MemoryDiagnostic diagnostic = {0};
    diagnostic.total_memory = mm->total_size;
    diagnostic.used_memory = 0;
    diagnostic.free_memory = 0;
    diagnostic.total_blocks = (mm->total_size)/(mm->block_size);
    diagnostic.used_blocks = 0;
    diagnostic.free_blocks = 0;

    calculate_diagnostic(&diagnostic, mm->root, mm->total_size, mm->block_size);

    return diagnostic;
}