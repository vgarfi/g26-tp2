/**
 * @file memoryManagerADT.h
 * @brief Definición del MemoryManagerADT para el memory manager.
 */

#ifndef memoryManagerADT_H
#define memoryManagerADT_H

#include <stdint.h>

/**
 * @typedef MemoryManagerADT
 * @brief Un puntero a una estructura concreta que representa el administrador de memoria.
 */
typedef struct MemoryManagerCDT* MemoryManagerADT;

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

#endif