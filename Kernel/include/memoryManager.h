#ifndef memoryManager_H
#define memoryManager_H
#include "lib.h"

typedef struct MemoryManagerCDT * MemoryManagerADT;

void *malloc_mm(MemoryManagerADT mm, uint32_t size);
void free_mm(MemoryManagerADT mm, void* ptr);
MemoryManagerADT initialize_mm(void* base, uint32_t size, uint32_t block_size);
#endif