#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memoryManagerADT.h>

#define SPLIT               2
#define FREE                1
#define NOT_FREE            0

typedef struct BuddyNode BuddyNode;

BuddyNode* find_parent(BuddyNode* root, BuddyNode* node);
size_t get_block_looked_size(size_t real_size);

struct BuddyNode {
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

MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    
    mm->block_size = get_block_looked_size(block_size);
    int aux_height = get_height(get_block_looked_size(size) - sizeof(MemoryManagerCDT), mm->block_size);
    int aux_node_qty = get_qty_nodes(aux_height);

    mm->total_size = get_max_size(size - sizeof(MemoryManagerCDT) - sizeof(BuddyNode) * aux_node_qty, mm->block_size);

    mm->height = get_height(mm->total_size, mm->block_size);
    mm->nodes_qty = get_qty_nodes(mm->height);

    mm->base = (void*)((char*)base + sizeof(MemoryManagerCDT) + sizeof(BuddyNode) * mm->nodes_qty);
    mm->root = (BuddyNode*)((char*)base + sizeof(MemoryManagerCDT));

    // Inicializar todos los nodos BuddyNode
    for (int i = 0; i < mm->nodes_qty; i++) {
        mm->root[i].free = FREE;
    }
    
    // Verifica si 'mm->root' apunta a la misma dirección esperada después de asignarlo.
    printf("mm->root: %p\n", (void*)mm->root);
    printf("First BuddyNode address: %p\n", (void*)&mm->root[0]);

    return mm;
}

BuddyNode* get_free_node(BuddyNode* root, size_t required_size, size_t block_size, int height, int* index, int current_height) {
    if (root == NULL) return NULL;

    BuddyNode* current = &root[*index];

    // Si el nodo está libre y del tamaño adecuado, se puede asignar
    if (current->free == FREE && block_size == required_size) {
        current->free = NOT_FREE;
        return current;
    }

    // Si el nodo es más grande que lo necesario, se necesita dividir
    if (current->free == SPLIT || (current->free == FREE && block_size > required_size && height > current_height)) {
        if (current->free == FREE) { 
            current->free = SPLIT;
        }
        //printf("nodo en el indice %d marcado como split\n", *index);

        size_t new_block_size = block_size / 2;

        int aux_index = *index;

        *index = 2 * aux_index + 1;

        // Intentar obtener un nodo en la mitad izquierda
        BuddyNode* found = NULL;
        found = get_free_node(root, required_size, new_block_size, height, index, current_height+1);

        // Si no se encontró en la izquierda, intentar en la derecha
        if (found == NULL) {
            *index = 2 * aux_index + 2;
            found = get_free_node(root, required_size, new_block_size, height, index, current_height+1);
        }

        return found;
    }

    return NULL; // No se encontró nodo adecuado
}

int calculate_offset(int looked_index, int size, int current_index, int* current_offset, int node_qty){
    if(looked_index == current_index){
        return 1;
    }
    if (current_index*2+1 > node_qty){
        return 0;
    }

    if(calculate_offset(looked_index, size/2, current_index*2 + 1, current_offset, node_qty) == 1)
        return 1;


    if (current_index*2+2 > node_qty){
        return 0;
    }

    *current_offset += size / 2;
    if(calculate_offset(looked_index, size/2, current_index*2 + 2, current_offset, node_qty) == 1)
        return 1;
    else
    {
        *current_offset -= size/2;
        return 0;
    }
}

void* malloc_mm(MemoryManagerADT mm, size_t size) {
    if (size == 0 || size > mm->total_size) {
        return NULL;
    }

    size_t block_looked_size = get_block_looked_size(size);
    if (block_looked_size < mm->block_size) {
        block_looked_size = mm->block_size;
    }
    //printf("looked size: %ld\n", block_looked_size);

    int index = 0;
    BuddyNode* node = get_free_node(mm->root, block_looked_size, mm->total_size, mm->height, &index, 0);
    //printf("indice: %d\n", index);
    if (node == NULL) {
        return NULL; // No hay bloques libres del tamaño adecuado
    }

    // Calcular el offset desde la base
    int offset = 0;
    int ret = calculate_offset(index, mm->total_size, 0, &offset, mm->nodes_qty);

    printf("offset calculado para bloque de %ld con ret valiendo %d: %d\n", block_looked_size, ret, offset);

    if (ret == 0) return NULL;

    return (void*)((char*)mm->base + offset);
}

void merge_brother_buddies(int node_index, BuddyNode* root) {
    while (node_index > 0) {
        int buddy_index;
        if(node_index % 2 == 0){
            buddy_index = node_index - 1;
        }else{
            buddy_index = node_index + 1;
        }

        // Verifica si el nodo actual y el hermano están libres
        if (root[node_index].free == FREE && root[buddy_index].free == FREE) {
            int parent_index = (node_index - 1) / 2;
            root[parent_index].free = FREE;

            node_index = parent_index;
        } else {
            break;
        }
    }
}

int calculate_node_offset(void *ptr, void* base, int* node_index, BuddyNode* root, int current_size, int block_size, int node_qty){
    if(ptr == base){ // encontre el indice entonces ahora tengo que recorrer todo a la izquierda posible
        while((&root[*node_index])->free == SPLIT){
            *node_index = (*node_index)*2 + 1;
        }
        return 1;
    }
    int node_index_aux = *node_index;
    *node_index = (*node_index) * 2 + 1;

    if(*node_index >= node_qty) return 0;

    if(calculate_node_offset(ptr, base, node_index, root, current_size/2, block_size, node_qty) == 1){
        return 1;
    } else
    {
        *node_index = (*node_index - 1) / 2;
        return 0;
    }
    

    *node_index = node_index_aux * 2 + 2;

    if(*node_index >= node_qty) return 0;

    if(calculate_node_offset(ptr, (void*)((char*) base + current_size / 2), node_index, root, current_size/2, block_size, node_qty) == 1){
        return 1;
    } else {
        *node_index = (*node_index - 2) / 2;
        return 0;
    }     
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    if (ptr == NULL || ptr < mm->base || ptr >= (mm->base + mm->total_size)) {
        return;
    }

    // Encuentra el nodo a liberar
    int node_offset = 0;
    calculate_node_offset(ptr, mm->base, &node_offset, mm->root, mm->total_size, mm->block_size, mm->nodes_qty);

    BuddyNode* node = &(mm->root[node_offset]);

    // Liberar nodo
    node->free = FREE;

    // Intentar fusionar con nodos hermano
    merge_brother_buddies(node_offset, mm->root);
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