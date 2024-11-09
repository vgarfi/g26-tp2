/**
 * @file memoryManagerADT.h
 * @brief Memory Manager ADT definition for memory management.
 */

#ifndef memoryManagerADT_H
#define memoryManagerADT_H

#include <stdint.h>
#include <stddef.h>

/**
 * @typedef MemoryManagerADT
 * @brief A pointer to a concrete structure representing the memory manager.
 */
typedef struct MemoryManagerCDT* MemoryManagerADT;

/**
 * @typedef MemoryDiagnostic
 * @brief Structure that encapsulates the state information of a memory manager.
 */
typedef struct {
    size_t total_memory;
    size_t used_memory;
    size_t free_memory;
    size_t total_blocks;
    size_t used_blocks;
    size_t free_blocks;
} MemoryDiagnostic;

/**
 * @brief Initializes the memory manager.
 *
 * @param base Pointer to the base of the memory to be managed.
 * @param size Total size of the memory to be managed.
 * @param block_size Size of each memory block.
 * @return A new initialized MemoryManagerADT.
 */
MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size);

/**
 * @brief Allocates memory to accommodate the desired size.
 *
 * @param mm The memory manager.
 * @param size The size of memory to allocate.
 * @return A pointer to the allocated memory block, or NULL if there is not enough memory.
 */
void* malloc_mm(MemoryManagerADT mm, size_t size);

/**
 * @brief Frees a previously allocated memory block.
 *
 * @param mm The memory manager.
 * @param ptr Pointer to the memory block to free.
 */
void free_mm(MemoryManagerADT mm, void* ptr);

/**
 * @brief Obtains relevant information about the memory.
 *
 * @param mm The memory manager.
 * @return The memory diagnostic of the memory manager.
 */
MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm);

#endif