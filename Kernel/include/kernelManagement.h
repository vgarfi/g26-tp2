#include "memory/memoryManagerADT.h"

#ifndef KERNEL_MANAGEMENT_H
#define KERNEL_MANAGEMENT_H

#define SHELL_PROCESS       "shell"
#define SHELL_PRIORITY      1

#define IDLE_PROCESS       "idle"
#define IDLE_PRIORITY       1 

#define PUPU_PROCESS       "pupu"
#define PUPU_PRIORITY       2


void initialize_management(void);
int64_t idle_process(int argc, char* argv);
int64_t pupu_process(int argc, char* argv);


#endif