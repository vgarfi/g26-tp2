#include "../include/scheduler/scheduler.h"
#include "../include/process/process.h"
#include "../kernel.c"

#define STACK_SIZE     128

uint8_t create_process(void) {
    void* ptr = malloc_mm(memory_manager, 1024);
    if (ptr == NULL) {
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE;

    add_pcb(stack_base, next_process_index);
    return next_process_index++;
}