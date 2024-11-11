// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <scheduler/scheduler.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <pipe/pipe.h>
#include <interrupts.h>
#include <videoDriver.h>
#include <string.h>
#include <time.h>
#include <fonts.h>

#define PS_COLUMN_WIDTH 11

extern MemoryManagerADT memory_manager;

uint8_t pids[MAX_PROCESSES] = {AVAILABLE_PID};
extern int shell_pid;
extern TQueueADT pcb_readies_queue;
TPCB* pcb_array[MAX_PROCESSES];

int max_pid;

void free_process(TPCB* pcb);
uint32_t get_state_color(TState state);
void destroy_anonymous_pipes(int fd);
int forced_kill_process(uint8_t pid);
void forced_kill_children(uint8_t m_pid);

int create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**), TScope scope) {
    char* ptr = malloc_mm(memory_manager, PROCESS_SIZE);
    if (ptr == NULL) {
        return -1;
    }

    int pid = get_available_pid();
    if (pid == -1) {
        return -1;
    }
    
    if (pid > max_pid) {
        max_pid = pid;
    }

    void* stack_base = ptr + STACK_SIZE;

    add_pcb(name, argc, argv, ptr, stack_base, (uint8_t) pid, priority, code, scope);    
    pids[pid] = NOT_AVAILABLE_PID;
    return pid;
}

int yield_process(void) {
    TPCB* pcb_to_yield = get_running_pcb();
    if (pcb_to_yield == NULL){
        return -1;
    }
    pcb_to_yield->state = READY;
    remove_pcb_from_queue(pcb_to_yield);
    for (uint8_t i = pcb_to_yield->priority; i > 0; i--) {
        enqueue(pcb_readies_queue, pcb_to_yield);
    }
    request_schedule();
    return 0;
}

int block_process(uint8_t pid) {
    TPCB* pcb_to_block = get_pcb_by_pid(pid);
    if (pcb_to_block == NULL){
        return -1;
    }
    remove_pcb_from_queue(pcb_to_block);
    TState state = pcb_to_block->state; 
    pcb_to_block->state = BLOCKED;
    if (state == RUNNING) {
        request_schedule();
    }
    return EXIT_SUCCESS;
}

int unblock_process(uint8_t pid) {
    TPCB* pcb_to_unblock = get_pcb_by_pid(pid);
    if (pcb_to_unblock == NULL){
        return -1;
    }
    pcb_to_unblock->state = READY;
    for (uint8_t i = pcb_to_unblock->priority; i > 0; i--) {
        enqueue(pcb_readies_queue, pcb_to_unblock);
    }
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

int get_process_scope(uint8_t pid) {
    TPCB* process_pcb = get_pcb_by_pid(pid);
    if (process_pcb == NULL){
        return -1;
    }
    return process_pcb->scope;
}

void add_pcb(char* name, uint64_t argc, char *argv[], char* stack_limit, char* stack_base, uint8_t pid, uint8_t priority, int64_t (*code)(int, char**), TScope scope) {
    if (name == NULL || argv == NULL || stack_base == NULL) {
        return;
    }

    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL) {
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

    new_pcb->argc = argc;

    char** argv_copy = (char **) malloc_mm(memory_manager, (argc * sizeof(char*)));
    if (argv_copy == NULL) {
        free_mm(memory_manager, new_pcb->name);
        free_mm(memory_manager, new_pcb);
        return;
    }
    
    for (int i = 0; i < argc; i++) {
    if (argv[i] != NULL) {
        argv_copy[i] = (char *) malloc_mm(memory_manager, strlen(argv[i]) + 1);
        if (argv_copy[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free_mm(memory_manager, argv_copy[j]);
            }
            free_mm(memory_manager, argv_copy);
            free_mm(memory_manager, new_pcb->name);
            free_mm(memory_manager, new_pcb);
            return;
        }
        strcpy(argv_copy[i], argv[i]);
    }
}

    new_pcb->argv = argv_copy;
    
    create_initial_stack((TStackFrame*) new_pcb->rsp, stack_base, argc, (uint64_t)argv_copy, code);

    new_pcb->state = READY;
    new_pcb->priority = priority;

    TPCB * mother_pcb = get_running_pcb();
    if (mother_pcb != NULL) {        
        new_pcb->fd_r = mother_pcb->fd_r;
        new_pcb->fd_w = mother_pcb->fd_w;
    } else {
        new_pcb->fd_r = STDIN;
        new_pcb->fd_w = STDOUT;
    }

    new_pcb->scope = scope;

    int name_lenght = strlen(name);
    char sem_name[name_lenght+5];
    char pid_name[5];
    itoa(pid, pid_name, 10);
    strconcat(sem_name, pid_name, name);
    
    new_pcb->semaphore = create_sem(sem_name, 0);
    
    if (new_pcb->semaphore == NULL) {
        free_mm(memory_manager, new_pcb);
    	return;
    }

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
    int current_pid = get_current_pid();
    kill_process(current_pid);
}

void wait_process_by_pid(uint8_t pid){
    TPCB* pcb_to_wait = get_pcb_by_pid(pid);
    if (pcb_to_wait == NULL){
        return;
    }
    if (pcb_to_wait->semaphore != NULL && pcb_to_wait->semaphore->name != NULL) {
        wait_sem(pcb_to_wait->semaphore->name);
    }
    free_process(pcb_to_wait);
    pids[pid] = AVAILABLE_PID;
    pcb_array[pid] = NULL;
}

int set_read_filedescriptor(uint8_t pid, int fd) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    process_pcb->fd_r = fd;
    return 0;
}
int set_write_filedescriptor(uint8_t pid, int fd) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    process_pcb->fd_w = fd;
    return 0;
}

int get_read_filedescriptor(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    return process_pcb->fd_r ;
}

int get_write_filedescriptor(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    return process_pcb->fd_w;
}

int kill_process(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    remove_pcb_from_queue(process_pcb);
    if (process_pcb->semaphore != NULL && process_pcb->semaphore->name != NULL) {
        post_sem(process_pcb->semaphore->name);
    }
    TState process_state = process_pcb->state;
    process_pcb->state = ZOMBIE;
    put_children_mpid_init(pid);
    destroy_anonymous_pipes(process_pcb->fd_r);
    if (process_state == RUNNING) {
        request_schedule();
    }
    return EXIT_SUCCESS;
}

int forced_kill_process(uint8_t pid) {
    TPCB* process_pcb  = get_pcb_by_pid(pid);
    if (process_pcb == NULL) {
        return -1;
    }
    remove_pcb_from_queue(process_pcb);
    if (process_pcb->semaphore != NULL && process_pcb->semaphore->name != NULL) {
        post_sem(process_pcb->semaphore->name);
    }
    forced_kill_children(pid);
    TState process_state = process_pcb->state;
    process_pcb->state = KILLED;

    destroy_anonymous_pipes(process_pcb->fd_r);
    destroy_anonymous_pipes(process_pcb->fd_w);
    
    free_process(process_pcb);

    pids[pid] = AVAILABLE_PID;
    pcb_array[pid] = NULL;

    if (process_state == RUNNING) {
        request_schedule();
    }
    return EXIT_SUCCESS;
}
void destroy_anonymous_pipes(int fd){
    if (!is_anonymous_pipe(fd/2)) {
        return;
    }
    close_pipe(fd/2);
}

void force_kill_piped_processes(int fd) {
    char is_write_fd = (fd % 2) != 0;
    for (int i = shell_pid+1; i <= max_pid; i++) {
        if (pcb_array[i] != NULL) {
            if ((is_write_fd && pcb_array[i]->fd_r == fd-1) || (!is_write_fd && pcb_array[i]->fd_w == fd+1)) {
                forced_kill_process(pcb_array[i]->pid);
            }
        }
    }
}


void forced_kill_children(uint8_t m_pid) {
    for (int i = 0; i <= max_pid; i++) {
        if (pcb_array[i] != NULL && pcb_array[i]->m_pid == m_pid) {
            forced_kill_process(pcb_array[i]->pid);
        }
    }
}

void free_process(TPCB* pcb){
    if (pcb == NULL) return;
    
    if(pcb->semaphore != NULL){
        delete_sem(pcb->semaphore->name);
    }
    
    if (pcb->stack_limit != NULL){
        free_mm(memory_manager, pcb->stack_limit);
    }

    if(pcb->name != NULL){
        free_mm(memory_manager, pcb->name);
    }

    if (pcb->argv != NULL) {
        for (int i = 0; i < pcb->argc; i++) {
            if (pcb->argv[i] != NULL) {
                free_mm(memory_manager, pcb->argv[i]);
            }
        }
        free_mm(memory_manager, pcb->argv);
    }

    free_mm(memory_manager, pcb);
}


uint32_t get_state_color(TState state) {
    switch (state)
    {
    case BLOCKED:
        return 0x00C72C29;
        break;
        
    case READY:
        return 0x00FFE47B;
        break;

    case RUNNING:
        return 0x005BD608;
        break;

    case KILLED:
        return 0x00AB0707;
        break;

    case ZOMBIE:
        return 0x0021851E;
        break;
    
    default:
        return 0x00FFFFFF;
    }
}


uint32_t get_scope_color(TScope scope) {
    switch (scope)
    {
    case FOREGROUND:
        return 0x00F0F0F0;
        break;
        
    case BACKGROUND:
        return 0x00787878;
        break;
    default:
        return 0x00FFFFFF;
    }
}

int processes_information() {
    int zoom_level = get_zoom();
    set_zoom(2);
    char buffer[64];
    char* states_labels[] = {"BLOCKED","READY","RUNNING","KILLED","ZOMBIE"};
    char* scope_labels[] = {"FOREGROUND","BACKGROUND"};
    vd_print("\n", 0x00FFFFFF);
    vd_print_padded("PID", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("Name", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("Mother PID", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("Priority", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("SP", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("BP", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("State", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("FDs", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print_padded("Scope", 0x00FFFFFF, PS_COLUMN_WIDTH);
    vd_print("\n", 0x00FFFFFF);

    for (int i = 0; i <= max_pid; i++) {
        if (pcb_array[i] != NULL) {
            itoa(i, buffer, 10);
            vd_print_padded(buffer, 0x00FFFFFF, PS_COLUMN_WIDTH);

            vd_print_padded(pcb_array[i]->name, 0x0000D4C1, PS_COLUMN_WIDTH);

            itoa(pcb_array[i]->m_pid, buffer, 10);
            vd_print_padded(buffer, 0x00FFFFFF, PS_COLUMN_WIDTH);

            itoa(pcb_array[i]->priority, buffer, 10);
            vd_print_padded(buffer, 0x00FFFFFF, PS_COLUMN_WIDTH);

            vd_print("0x", 0x00FFFFFF);
            itoa64((uint64_t) pcb_array[i]->rsp, buffer, 16);
            vd_print_padded(buffer, 0x00FFFFFF, PS_COLUMN_WIDTH - 2);

            vd_print("0x", 0x00FFFFFF);
            itoa64((uint64_t) pcb_array[i]->stack_base, buffer, 16);
            vd_print_padded(buffer, 0x00FFFFFF, PS_COLUMN_WIDTH - 2);

            vd_print_padded(states_labels[pcb_array[i]->state], get_state_color(pcb_array[i]->state), PS_COLUMN_WIDTH);

            itoa(pcb_array[i]->fd_r, buffer, 10);
            vd_print("[", 0x00FFFFFF);
            vd_print(buffer, 0x00FFFFFF);
            vd_print(",", 0x00FFFFFF);
            itoa(pcb_array[i]->fd_w, buffer, 10);
            vd_print(buffer, 0x00FFFFFF);
            vd_print("]", 0x00FFFFFF);
            vd_print_padded("", 0x00FFFFFF, PS_COLUMN_WIDTH - strlen(buffer) - 3);

            vd_print_padded(scope_labels[pcb_array[i]->scope], get_scope_color(pcb_array[i]->scope), PS_COLUMN_WIDTH);

            vd_print("\n", 0x00FFFFFF);
        }
    }
    set_zoom(zoom_level);
    return EXIT_SUCCESS;
}

int64_t idle_process(int argc, char** argv) {
    while (1) {
        _hlt();
    }
}

int64_t init_process(int argc, char** argv) {
    uint64_t init_pid = get_current_pid();
    while(1) {
        for(int i = init_pid+1; i <= max_pid; i++) {
            if (pcb_array[i] != NULL && pcb_array[i]->m_pid == init_pid && pcb_array[i]->state == ZOMBIE) {
                pcb_array[i]->state = KILLED;
                free_process(pcb_array[i]);
                pcb_array[i] = NULL;
                pids[i] = AVAILABLE_PID;
            }
        }
    }
}