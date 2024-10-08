#include <scheduler/scheduler.h>
#include <process/process.h>
#include <string.h>
#include <interrupts.h>
#include "../kernel.h"

uint8_t pids[MAX_PROCESSES] = {AVAILABLE_PID};

void initialize_process_management(void) { // TODO esta función debería crear la shell
    // TODO: no deberia usar create_process sino mas bien un create_process_with_pid o algo asi porque el pid del idle deberia ser 0 siempre
    int idle_pid = create_process(IDLE_PROCESS, 0, idle_args, IDLE_PRIORITY, &idle_process);
}

int64_t idle_process(int, char**){
    while (1) {
		_hlt();
	}
}

int create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**)) {
    void* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        return -1;
    }

    int pid = get_available_pid();
    if (pid == -1){
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE; // si el malloc devuelve alineado esto no hace falta alinearlo, ya esta (tambien STACK_SIZE tiene que ser multiplo de 8)
    create_initial_stack((uint64_t *)stack_base, argc, argv, code, &wrapper);
    add_pcb(name, argc, argv, stack_base, (uint8_t) pid, priority);
    
    pids[pid] = NOT_AVAILABLE_PID;
    
    return pid;
}

void add_pcb(char* name, uint64_t argc, char *argv[], void* stack_base, uint8_t pid, uint8_t priority) {
    if (name == NULL || argc < 0 || argv == NULL || stack_base == NULL) {
        return;
    }

    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL) {
        free_mm(memory_manager, new_pcb);
        return;
    }
    
	new_pcb->name = (char *) malloc_mm(memory_manager, strlen(name) + 1); // strlen esta en string.h
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

int get_available_pid() {
    for(int pid = 0; pid < MAX_PROCESSES; pid++){
        if (pids[pid] == AVAILABLE_PID){
            return AVAILABLE_PID;
        }
    }
    return -1;
}

void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**)) {
    code(argc, argv);
    kill_process(get_current_pid());
}

int kill_process(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    process_pcb->state = KILLED;
    kill_pcb(process_pcb);
    pids[pid] = AVAILABLE_PID;
    requestSchedule();
    return EXIT_SUCCESS;
}