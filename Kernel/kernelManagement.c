// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <memory/memoryManagerADT.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <synchro/synchro.h>
#include <pipe/pipe.h>
#include <interrupts.h>
#include <keyboardDriver.h>
#include <string.h>

char* init_args[] = {INIT_PROCESS, 0};
char* idle_args[] = {IDLE_PROCESS, 0};
char* shell_args[] = {SHELL_PROCESS, 0};

MemoryManagerADT memory_manager;

typedef int64_t (*EntryPoint)(int, char**);

void * sample_code_module_address = (void*)0x400000;
void * sample_data_module_address = (void*)0x500000;
void * memory_base_address = (void*)0x600000;

int init_pid;
int idle_pid;
int shell_pid;

void initialize_management(void){
	memory_manager = initialize_mm(memory_base_address, MEMORY_SIZE, MEMORY_BLOCK_SIZE);
	initialize_synchro();
    initialize_scheduling();
    initialize_pipes();
    initialize_keyboard();
    init_pid = create_process(INIT_PROCESS, 1, init_args, INIT_PRIORITY, (int64_t (*)(int, char**)) init_process, BACKGROUND);
    idle_pid = create_process(IDLE_PROCESS, 1, idle_args, IDLE_PRIORITY, (int64_t (*)(int, char**)) idle_process, BACKGROUND);
    shell_pid = create_process(SHELL_PROCESS, 3, shell_args, SHELL_PRIORITY, sample_code_module_address, FOREGROUND);
}