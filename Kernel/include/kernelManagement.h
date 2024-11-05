#include "memory/memoryManagerADT.h"

#ifndef KERNEL_MANAGEMENT_H
#define KERNEL_MANAGEMENT_H

#define STACK_SIZE          2048
#define PROCESS_SIZE        STACK_SIZE
#define MAX_PROCESSES       (MEMORY_SIZE/PROCESS_SIZE)/1024

#define INIT_PROCESS       "init"
#define INIT_PRIORITY       1

#define IDLE_PROCESS       "idle"
#define IDLE_PRIORITY       1

#define SHELL_PROCESS       "shell"
#define SHELL_PRIORITY      10

#define LOOP_PROCESS        "loop"
#define LOOP_PRIORITY       1


#define MEMORY_SIZE         (1024*1024*512)
#define MEMORY_BLOCK_SIZE   (1024*8)

#define STDIN               0
#define STDOUT              1

void initialize_management(void);

#endif