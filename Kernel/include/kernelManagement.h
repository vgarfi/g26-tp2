#include "memory/memoryManagerADT.h"

#ifndef KERNEL_MANAGEMENT_H
#define KERNEL_MANAGEMENT_H

#define SHELL_PROCESS       "shell"
#define SHELL_PRIORITY      10

#define IDLE_PROCESS       "idle"
#define IDLE_PRIORITY       1

#define MEMORY_SIZE         (1024*1024)
#define MEMORY_BLOCK_SIZE   (1024*8)

void initialize_management(void);
int64_t idle_process(int argc, char* argv);

#endif