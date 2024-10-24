#include <memory/memoryManagerADT.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <interrupts.h>
#include <string.h>

char* shell_args[] = {SHELL_PROCESS, 0};
char* idle_args[] = {IDLE_PROCESS, 0};

MemoryManagerADT memory_manager;

typedef int64_t (*EntryPoint)(int, char**);

void * sampleCodeModuleAddress = (void*)0x400000;
void * sampleDataModuleAddress = (void*)0x500000;
void * memoryBaseAddress = (void*)0x600000;


void initialize_management(void){
	memory_manager = initialize_mm(memoryBaseAddress, MEMORY_SIZE, MEMORY_BLOCK_SIZE);
    create_process(IDLE_PROCESS, 1, idle_args, IDLE_PRIORITY, idle_process);
    create_process(SHELL_PROCESS, 3, shell_args, SHELL_PRIORITY, sampleCodeModuleAddress);
}

int64_t idle_process(int argc, char* argv) {
    while (1) {
        _hlt();
    }
}