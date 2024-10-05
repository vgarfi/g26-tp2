/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include "../memory/memoryManagerADT.h"
#define MAX_PROCESSES   1024

int next_process_index = 0;

uint8_t create_process (char* name, uint64_t argc, char *argv[], uint8_t priority);

#endif