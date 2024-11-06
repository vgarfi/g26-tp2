#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memoryManagerADT.h>

#define SPLIT               2
#define FREE                1
#define NOT_FREE            0

typedef struct BuddyNode BuddyNode;

BuddyNode* find_parent(BuddyNode* root, BuddyNode* node);
void split_node(BuddyNode* current, int remaining_nodes);
size_t get_block_looked_size(size_t real_size);

struct BuddyNode {
    BuddyNode *next;
    char free; // 0 = usado, 1 = libre, 2 = split
};

typedef struct MemoryManagerCDT {
    void* base;
    size_t total_size;
    size_t block_size;
    BuddyNode * root;
    int nodes_qty;
    int height;
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
        return -1; // o un valor adecuado de error
    }
    return log2(size/block_size);
}

int get_qty_nodes(int height){
    return (int)(pow(2, height+1) - 1);
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

BuddyNode* find_parent(BuddyNode* root, BuddyNode* node) {
    if (node == root) {
        return NULL; // La raíz no tiene un padre
    }

    // Calcular el índice del nodo en el array
    int node_index = node - root;
    int parent_index = (node_index - 1) / 2;

    // Retornar el nodo padre
    return &root[parent_index];
}

MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    
    mm->block_size = get_block_looked_size(block_size);
    mm->total_size = get_max_size(size - sizeof(MemoryManagerCDT), mm->block_size);

    mm->height = get_height(mm->total_size, mm->block_size);
    mm->nodes_qty = get_qty_nodes(mm->height);

    mm->base = (void*)((char*)base + sizeof(MemoryManagerCDT) + sizeof(BuddyNode) * mm->nodes_qty);
    mm->root = (BuddyNode*)((char*)base + sizeof(MemoryManagerCDT));

    // Inicializar todos los nodos BuddyNode
    for (int i = 0; i < mm->nodes_qty; i++) {
        BuddyNode* node = &mm->root[i];
        node->free = FREE;
        node->next = NULL;
    }
    mm->root->free = FREE;
    
    return mm;
}

BuddyNode* get_free_node(BuddyNode* root, size_t required_size, size_t block_size, int height) {
    if (root == NULL) return NULL;

    // Si el nodo está libre y del tamaño adecuado, se puede asignar
    if (root->free == FREE && required_size == block_size) {
        root->free = NOT_FREE;
        return root;
    }

    // Si el nodo está dividido o demasiado grande, se necesita buscar o dividir más
    if (root->free == SPLIT || block_size > required_size) {
        size_t new_block_size = block_size / 2;
        BuddyNode* left = &root[1];  // Nodo izquierdo
        BuddyNode* right = &root[(1 << (height - 1))]; // Nodo derecho (la mitad del árbol)

        BuddyNode* found = get_free_node(left, required_size, new_block_size, height - 1);
        if (found == NULL) {
            found = get_free_node(right, required_size, new_block_size, height - 1);
        } else {
            root->free = SPLIT; // Marcar como dividido
        }
        return found;
    }

    return NULL; // No se encontró nodo adecuado
}

void* malloc_mm(MemoryManagerADT mm, size_t size) {
    if (size == 0 || size > mm->total_size) {
        return NULL;
    }

    size_t block_looked_size = get_block_looked_size(size);
    if (block_looked_size < mm->block_size) {
        block_looked_size = mm->block_size;
    }

    BuddyNode* node = get_free_node(mm->root, block_looked_size, mm->total_size, mm->height);
    if (node == NULL) {
        return NULL; // No hay bloques libres del tamaño adecuado
    }

    // Calcular el offset desde la base
    int offset = (node - mm->root) * block_looked_size;
    return (void*)((char*)mm->base + offset);
}

BuddyNode* find_buddy_node(MemoryManagerADT mm, BuddyNode* node) {
    int node_index = node - mm->root;
    int buddy_index = node_index ^ 1; // XOR para encontrar el buddy
    return &mm->root[buddy_index];
}

void merge_brother_buddies(BuddyNode* node, BuddyNode* root) {
    while (node->free == FREE) {
        BuddyNode* buddy = find_buddy_node(root, node);

        if (buddy->free != FREE) {
            break;
        }

        // Marcar el nodo padre como libre
        BuddyNode* parent = find_parent(root, node);
        if (parent == NULL) {
            break;
        }

        parent->free = FREE;
        node = parent; // Ahora subimos al nodo padre
    }
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    if (ptr == NULL || ptr < mm->base || ptr >= (mm->base + mm->total_size)) {
        return;
    }

    size_t offset = (char*)ptr - (char*)mm->base;
    size_t block_size = mm->block_size;

    // Encuentra el nodo a liberar
    BuddyNode* node = &mm->root[offset / block_size];

    // Liberar nodo
    node->free = FREE;

    // Intentar fusionar con nodos hermano
    merge_brother_buddies(node, mm->root);
}

/*void calculate_diagnostic(MemoryDiagnostic* diagnostic, BuddyNode* node, size_t current_size, size_t block_size) {
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
}*/

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm) {
    MemoryDiagnostic diagnostic = {0};
    diagnostic.total_memory = mm->total_size;
    diagnostic.used_memory = 0;
    diagnostic.free_memory = 0;
    diagnostic.total_blocks = (mm->total_size)/(mm->block_size);
    diagnostic.used_blocks = 0;
    diagnostic.free_blocks = 0;

    //calculate_diagnostic(&diagnostic, mm->root, mm->total_size, mm->block_size);

    return diagnostic;
}