#include <scheduler/scheduler.h>
#include <process/process.h>
#include "../kernel.c"

#define STACK_SIZE     128
#define PROCESS_SIZE   1024

int next_process_index = 0;

uint8_t create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**)) {
    void* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE; // si el malloc devuelve alineado esto no hace falta alinearlo, ya esta (tambien STACK_SIZE tiene que ser multiplo de 8)

    add_pcb(name, argc, argv, stack_base, next_process_index, priority);
    return next_process_index++;        // TODO: hay que recorrer porque se pueden matar procesos y esos PIDs se puede reutilizar
}

void add_pcb(char* name, uint64_t argc, char *argv[], void* stack_base, uint8_t pid, uint8_t priority) {
    if (name == NULL || argc < 0 || argv == NULL || stack_base == NULL) {
        return;
    } // TODO ver que hacemos con argc y argv

    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL) {
        free_mm(memory_manager, new_pcb);
        return;
    }
    
	new_pcb->name = (char *) malloc_mm(memory_manager, strlen(name) + 1);
	if (new_pcb->name == NULL) {
		free_mm(memory_manager, new_pcb);
		return;
	}

	strcpy(new_pcb->name, name);
    new_pcb->pid = pid;                 // TODO: hay que recorrer porque se pueden matar procesos y esos PIDs se puede reutilizar
    new_pcb->m_pid = get_current_pid();

    new_pcb->rsp = stack_base - sizeof(TStackFrame) - sizeof(TCodeFrame);
    new_pcb->state = READY;
    new_pcb->priority = priority;

    pcb_array[pid] = new_pcb;
    
    enqueue(pcb_readies_queue, new_pcb);
    return;
}