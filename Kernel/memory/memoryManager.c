#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/memoryManager.h"

typedef struct MemoryManagerCDT {
    unsigned char *bitmap;
    char *memory_base;
    size_t memory_size;
    size_t block_size;
} MemoryManagerCDT;

bool get_bit(unsigned char *bitmap, int index) {
    int byte_index = index / 8;
    int bit_index = index % 8;
    return (bitmap[byte_index] >> bit_index) & 1;
}

void set_bit(unsigned char *bitmap, int index, bool value) {
    int byte_index = index / 8;
    int bit_index = index % 8;
    
    if (value) {
        bitmap[byte_index] |= (1 << bit_index); 
    } else {
        bitmap[byte_index] &= ~(1 << bit_index); 
    }
}

void* malloc_mm(MemoryManagerADT mm, size_t size) {
    if (size > mm->block_size) {
        return NULL;
    }

    size_t num_blocks = mm->memory_size / mm->block_size;

    for (size_t i = 0; i < num_blocks; i++) {
        if (!get_bit(mm->bitmap, i)) {
            // Encontramos un bloque libre
            set_bit(mm->bitmap, i, true);
            return (void*)(mm->memory_base + (i * mm->block_size));
        }
    }

    return NULL;  // No hay bloques libres
}

void free_mm(MemoryManagerADT mm, void* ptr) {
    if (ptr == NULL) {
        return;
    }

    int block_index = ((char*)ptr - mm->memory_base) / mm->block_size;

    set_bit(mm->bitmap, block_index, false);
}


MemoryManagerADT initialize_mm(void* base, size_t memory_size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    size_t num_blocks = memory_size / block_size;
    size_t bitmap_size = (num_blocks + 7) / 8;

    mm->memory_size = memory_size;
    mm->block_size = block_size;

    mm->bitmap = (unsigned char*)((char*)base + sizeof(MemoryManagerCDT));
    mm->memory_base = (char*)mm->bitmap + bitmap_size;

    for (size_t i = 0; i < bitmap_size; i++) {
        mm->bitmap[i] = 1;
    }

    return mm;
}

