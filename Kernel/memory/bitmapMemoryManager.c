/**
 * @file bitmapMemoryManager.c
 * @brief Construcción de un Memory Manager basado en Bitmap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memoryManagerADT.h"

#define ALL_ONES 0xff

typedef struct MemoryManagerCDT {
    unsigned char *bitmap;          // Los bits para identificar bbloques libres
    char *memory_base;              // La dirección donde comienzan a guardarse los datos
    size_t memory_size;             // El tamaño total de la memoria
    size_t block_size;              // El tamaño de cada bloque de memoria
    size_t used_blocks;             // Cantidad de bloques usados
} MemoryManagerCDT;


MemoryManagerADT initialize_mm(void* base, size_t memory_size, size_t block_size) {
    MemoryManagerADT mm = (MemoryManagerADT)base;
    size_t max_num_blocks = memory_size / block_size;
    size_t bitmap_size = (max_num_blocks + 7) / 8; // TODO usar funcion ceil si podemos incluir de math

    mm->memory_size = memory_size - bitmap_size - sizeof(MemoryManagerCDT);
    mm->block_size = block_size;
    mm->used_blocks = 0;

    mm->bitmap = (unsigned char*)((char*)base + sizeof(MemoryManagerCDT));
    mm->memory_base = (char*)mm->bitmap + bitmap_size;

    for (size_t i = 0; i < bitmap_size; i++) {
        mm->bitmap[i] = ALL_ONES;
    }

    return mm;
}

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
        if (get_bit(mm->bitmap, i)) {
            // Encontramos un bloque libre
            set_bit(mm->bitmap, i, 0);
            mm->used_blocks++;
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
    set_bit(mm->bitmap, block_index, 1);
    mm->used_blocks--;
}

size_t get_used_memory(MemoryManagerADT mm) {
    size_t num_blocks = mm->memory_size / mm->block_size;
}

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm) { // TODO ver si trunca
    MemoryDiagnostic diagnostic;
    diagnostic.total_memory = mm->memory_size;
    diagnostic.used_memory = (mm->used_blocks * mm->block_size);
    diagnostic.free_memory = diagnostic.total_memory - diagnostic.used_memory;
    diagnostic.total_blocks = (mm->memory_size / mm->block_size);
    diagnostic.used_blocks = mm->used_blocks;
    diagnostic.free_blocks = diagnostic.total_blocks - diagnostic.used_blocks;
    return diagnostic;
}