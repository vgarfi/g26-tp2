#include <scheduler/scheduler.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <string.h>

extern MemoryManagerADT memory_manager;

uint8_t pids[MAX_PROCESSES] = {AVAILABLE_PID};

TPCB* pcb_array[MAX_PROCESSES];

int create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**)) {
    void* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        vdPrint("\nInvalid PID a la hora de crear", 0x00FFFFFF);
        return -1;
    }

    int pid = get_available_pid();
    if (pid == -1) {
        vdPrint("\nInvalid PID a la hora de buscar", 0x00FFFFFF);
        return -1;
    }

    void* stack_base = ptr + STACK_SIZE/sizeof(uint64_t) - 1;
    // create_initial_stack((uint64_t *)stack_base, argc, argv, code, &wrapper);
    add_pcb(name, argc, argv, ptr, stack_base, (uint8_t) pid, priority, code);
    
    pids[pid] = NOT_AVAILABLE_PID;
    return pid;
}

void add_pcb(char* name, uint64_t argc, char *argv[], uint64_t* stack_limit, uint64_t* stack_base, uint8_t pid, uint8_t priority, int64_t (*code)(int, char**)) {
    if (name == NULL || argc < 0 || argv == NULL || stack_base == NULL) {
        return;
    }

    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL) {
        vdPrint("\nNew Pcb dio NULL", 0x00FFFFFF);
        free_mm(memory_manager, new_pcb);
        return;
    }
    
	new_pcb->name = (char *) malloc_mm(memory_manager, strlen(name) + 1); // strlen esta en string.h
	if (new_pcb->name == NULL) {
		free_mm(memory_manager, new_pcb);
        vdPrint("\nNew pcb name dio NULL", 0x00FFFFFF);
		return;
	}

	strcpy(new_pcb->name, name);
    new_pcb->pid = pid;                 // TODO: hay que recorrer porque se pueden matar procesos y esos PIDs se puede reutilizar
    new_pcb->m_pid = get_current_pid();

    new_pcb->stack_base = stack_base;
    new_pcb->stack_limit = stack_limit;

    char buffer[50];
    // new_pcb->rsp = stack_base - sizeof(TStackFrame) - sizeof(TCodeFrame);
    new_pcb->rsp = stack_base - sizeof(TStackFrame)/sizeof(uint64_t) + 1;
    
    create_initial_stack((TStackFrame*) new_pcb->rsp, stack_base, argc, argv, code);

    itoa(new_pcb->stack_base, buffer, 10);
    vdPrint("\nPCB->stack_base: ", 0x00FFFFFF);
    vdPrint(buffer, 0x00FFFFFF);
    itoa(new_pcb->rsp, buffer, 10);
    vdPrint("\nPCB->rsp: ", 0x00FFFFFF);
    vdPrint(buffer, 0x00FFFFFF);

    new_pcb->state = READY;
    new_pcb->priority = priority;

    pcb_array[pid] = new_pcb;
    enqueue(pcb_readies_queue, new_pcb);
    return;
}

void create_initial_stack(TStackFrame* stack_initial_data, uint64_t* stack_base, uint64_t argc, uint64_t argv, int64_t (*code)(int, char**)) {
    // Esto simula los pushes para abajo
    stack_initial_data->rax = 0;
    stack_initial_data->rbx = 0;
    stack_initial_data->rcx = 0;
    stack_initial_data->rdx = 0;
    stack_initial_data->rbp = stack_base;
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
    stack_initial_data->rsp = stack_base + 1;
    stack_initial_data->rip = code; // TODO y la wrapper?
    stack_initial_data->cs = 0x08;
    stack_initial_data->rflags = 0x202;
    stack_initial_data->ss = 0;
    stack_initial_data->align = 0;
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