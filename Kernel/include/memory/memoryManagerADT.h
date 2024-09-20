/**
 * @file memoryManagerADT.h
 * @brief Definición del MemoryManagerADT para el memory manager.
 */

#ifndef memoryManagerADT_H
#define memoryManagerADT_H

#include <stdint.h>

/**
 * @typedef MemoryManagerADT
 * @brief Un puntero a una estructura concreta que representa el memory manager.
 */
typedef struct MemoryManagerCDT* MemoryManagerADT;

/**
 * @typedef MemoryDiagnostic
 * @brief Estructura que encapsula la información del estado de un memory manager.
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
 * @brief Inicializa el memory manager.
 *
 * @param base Puntero a la base de la memoria a gestionar.
 * @param size Tamaño total de la memoria a gestionar.
 * @param block_size Tamaño de cada bloque de memoria.
 * @return Un nuevo MemoryManagerADT inicializado.
 */
MemoryManagerADT initialize_mm(void* base, size_t size, size_t block_size);

/**
 * @brief Asigna memoria para alojar el tamaño deseado.
 *
 * @param mm El memory amnager.
 * @param size El tamaño de memoria a asignar.
 * @return Un puntero al bloque de memoria asignado, o NULL si no hay suficiente memoria.
 */
void* malloc_mm(MemoryManagerADT mm, size_t size);

/**
 * @brief Libera un bloque de memoria previamente asignado.
 *
 * @param mm El memory manager.
 * @param ptr Puntero al bloque de memoria a liberar.
 */
void free_mm(MemoryManagerADT mm, void* ptr);

/**
 * @brief Obtiene información relevante sobre la memoria.
 *
 * @param mm El memory manager.
 * @return El diagnostico de memoria del memory manager.
 */

MemoryDiagnostic get_diagnostic_mm(MemoryManagerADT mm);
#endif