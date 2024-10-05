#include "../include/scheduler/scheduler.h"
#include "../include/process/process.h"
#include "../kernel.c"

#define STACK_SIZE     128
#define PROCESS_SIZE   1024

uint8_t create_process(char* name, uint64_t argc, char *argv[], uint8_t priority) {
    void* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE;

    add_pcb(name, argc, argv, stack_base, next_process_index, priority);
    return next_process_index++;
}