#include <scheduler/scheduler.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <interrupts.h>
#include <videoDriver.h>
#include <string.h>

extern MemoryManagerADT memory_manager;

uint8_t pids[MAX_PROCESSES] = {AVAILABLE_PID};

extern TQueueADT pcb_readies_queue;
TPCB* pcb_array[MAX_PROCESSES];

void free_process(TPCB* pcb);

int create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**)) {
    char* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        vdPrint("\nKERNEL: OUT OF MEMEORY. Possible errors may ocurr", 0x00FF0000);
        return -1;
    }

    int pid = get_available_pid();
    if (pid == -1) {
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE;
    add_pcb(name, argc, argv, ptr, stack_base, (uint8_t) pid, priority, code);
    
    pids[pid] = NOT_AVAILABLE_PID;
    return pid;
}

int yield_process(void) {
    TPCB* pcb_to_yield = get_running_pcb();
    if (pcb_to_yield == NULL){
        return -1;
    }
    remove_pcb_from_queue(pcb_to_yield);
    for (uint8_t i = pcb_to_yield->priority; i > 0; i--) {
        enqueue(pcb_readies_queue, pcb_to_yield);
    }
    requestSchedule();
    return 0;
}

int block_process(uint8_t pid) {
    TPCB* pcb_to_block = get_pcb_by_pid(pid);
    if (pcb_to_block == NULL){
        return -1;
    }
    remove_pcb_from_queue(pcb_to_block);
    pcb_to_block->state = BLOCKED;
    return EXIT_SUCCESS;
}

int unblock_process(uint8_t pid) {
    TPCB* pcb_to_unblock = get_pcb_by_pid(pid);
    if (pcb_to_unblock == NULL){
        return -1;
    }
    for (uint8_t i = pcb_to_unblock->priority; i > 0; i--) {
        enqueue(pcb_readies_queue, pcb_to_unblock);
    }
    pcb_to_unblock->state = READY;

    return EXIT_SUCCESS;
}

int change_priority(uint8_t pid, uint8_t new_priority){
    TPCB* pcb_to_change = get_pcb_by_pid(pid);
    if (pcb_to_change == NULL){
        return -1;
    }
    pcb_to_change->priority = new_priority;
    return EXIT_SUCCESS;
}

void add_pcb(char* name, uint64_t argc, char *argv[], char* stack_limit, char* stack_base, uint8_t pid, uint8_t priority, int64_t (*code)(int, char**)) {
    if (name == NULL || argc < 0 || argv == NULL || stack_base == NULL) {
        return;
    }

    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL) {
        vdPrint("\nKERNEL: OUT OF MEMEORY. Possible errors may ocurr", 0x00FF0000);
        return;
    }
    
	new_pcb->name = (char *) malloc_mm(memory_manager, strlen(name) + 1);
	if (new_pcb->name == NULL) {
        free_mm(memory_manager, new_pcb);
    	return;
	}

	strcpy(new_pcb->name, name);
    new_pcb->pid = pid;
    new_pcb->m_pid = get_current_pid();

    new_pcb->stack_base = (uint64_t*) stack_base;
    new_pcb->stack_limit = (uint64_t*) stack_limit;

    new_pcb->rsp = (uint64_t *)(stack_base - sizeof(TStackFrame) + 1);
    
    create_initial_stack((TStackFrame*) new_pcb->rsp, stack_base, argc, (uint64_t)argv, code);

    new_pcb->state = READY;
    new_pcb->priority = priority;

    int name_lenght = strlen(name);
    char sem_name[name_lenght+5];
    char pid_name[5];
    itoa(pid, pid_name, 10); 
    strconcat(sem_name, pid_name, name);
    new_pcb->semaphore = create_sem(sem_name, 0);

    pcb_array[pid] = new_pcb;
    for (uint8_t i = priority; i > 0; i--) {
        enqueue(pcb_readies_queue, new_pcb);
    }
    return;
}

void create_initial_stack(TStackFrame* stack_initial_data, char* stack_base, uint64_t argc, uint64_t argv, int64_t (*code)(int, char**)) {
    // Esto simula los pushes para abajo
    stack_initial_data->rax = 0;
    stack_initial_data->rbx = 0;
    stack_initial_data->rcx = 0;
    stack_initial_data->rdx = (uint64_t)code;
    stack_initial_data->rbp = (uint64_t) stack_base;
    stack_initial_data->rdi = argc;
    stack_initial_data->rsi = argv;
    stack_initial_data->r8 = 0;
    stack_initial_data->r9 = 0;
    stack_initial_data->r10 = 0;
    stack_initial_data->r11 = 0;
    stack_initial_data->r12 = 0;
    stack_initial_data->r13 = 0;
    stack_initial_data->r14 = 0;
    stack_initial_data->r15 = 0;

    // Propio del IRETQ
    stack_initial_data->rsp = (uint64_t)stack_base;
    stack_initial_data->rip = (uint64_t)wrapper;
    stack_initial_data->cs = 0x08;
    stack_initial_data->rflags = 0x202;
    stack_initial_data->ss = 0;
    stack_initial_data->align = 0;
}

int get_available_pid() {
    for(int pid = 0; pid < MAX_PROCESSES; pid++){
        if (pids[pid] == AVAILABLE_PID){
            return pid;
        }
    }
    return -1;
}

void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**)) {
    code(argc, argv);
    kill_process(get_current_pid());
}

void wait_process_by_pid(uint8_t pid){
    TPCB* pcb_to_wait = get_pcb_by_pid(pid);
    if (pcb_to_wait == NULL){
        return -1;
    }
    wait_sem(pcb_to_wait->semaphore->name);
}

int kill_process(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    post_sem(process_pcb->semaphore->name);
    TState process_state = process_pcb->state;
    kill_pcb(process_pcb);
    process_pcb->state = ZOMBIE;
    pids[pid] = AVAILABLE_PID;
    process_pcb->m_pid = 0;
    if (process_state == RUNNING) {
        requestSchedule();
    }
    return EXIT_SUCCESS;
}

void free_process(TPCB* pcb){
    if (pcb == NULL) return;
    
    if(pcb->semaphore != NULL){
        delete_sem(pcb->semaphore->name);
    }
    
    if(pcb->stack_limit != NULL){
        free_mm(memory_manager, pcb->stack_limit);
    }

    if (pcb->rsp != NULL){
        free_mm(memory_manager, pcb->rsp);
    }
    
    if (pcb->stack_base != NULL){
        free_mm(memory_manager, pcb->stack_base);
    }

    if(pcb->name != NULL){
        free_mm(memory_manager, pcb->name);
    }

    free_mm(memory_manager, pcb);
}

int processes_information(void){
    char buffer[10];
    char* states_labels[] = {"BLOCKED","READY","RUNNING","KILLED","ZOMBIE"};
    for(int i = 0; i < MAX_PROCESSES; i++) {
        if (pcb_array[i] != NULL && pids[i] == NOT_AVAILABLE_PID) {
            vdPrint("\nPID: ", 0x00FFFFFF);
            itoa(i, buffer, 10);
            vdPrint(buffer, 0x00FFFFFF);
            vdPrint(" - MOTHER PID: ", 0x00FFFFFF);
            itoa(pcb_array[i]->m_pid, buffer, 10);
            vdPrint(buffer, 0x00FFFFFF);
            vdPrint(" - NAME: ", 0x00FFFFFF);
            vdPrint(pcb_array[i]->name, 0x00FFFFFF);
            vdPrint(" - PRIORITY: ", 0x00FFFFFF);
            itoa(pcb_array[i]->priority, buffer, 10);
            vdPrint(buffer, 0x00FFFFFF);
            vdPrint(" - SP: ", 0x00FFFFFF);
            itoa64((uint64_t) pcb_array[i]->rsp, buffer, 16);
            vdPrint(buffer, 0x00FFFFFF);
            vdPrint(" - BP: ", 0x00FFFFFF);
            itoa64((uint64_t) pcb_array[i]->stack_base, buffer, 16);
            vdPrint(buffer, 0x00FFFFFF);
            vdPrint(" - STATE: ", 0x00FFFFFF);
            vdPrint(states_labels[pcb_array[i]->state], 0x00FFFFFF);
        }
    }
    vdPrint("\n",0x00FFFFFF);
    return EXIT_SUCCESS;
}

int64_t init_process(int argc, char** argv) {
    uint64_t init_pid = get_current_pid();
    while(1) {
        for(int i = 0; i < MAX_PROCESSES; i++) {
            if (i != init_pid && pcb_array[i] != NULL && pcb_array[i]->m_pid == init_pid && pcb_array[i]->state == ZOMBIE) {
                pcb_array[i]->state = KILLED;
                free_process(pcb_array[i]);
            }
        }
    }
}