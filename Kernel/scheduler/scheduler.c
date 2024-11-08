#include <kernelManagement.h>
#include <process/process.h>
#include <scheduler/scheduler.h>
#include <videoDriver.h>
#include <interrupts.h>

extern TPCB* pcb_array[MAX_PROCESSES];
extern int max_pid;

TQueueADT pcb_readies_queue;
TPCB* running_pcb;

void initialize_scheduling(void) {
    pcb_readies_queue = createQueue();
}

int is_initialized(void){
    return pcb_array[0] != NULL;
}

int is_inside_process_boundaries(uint64_t* rsp) {
    return (rsp >= running_pcb->stack_limit && rsp <= running_pcb->stack_base);
}

uint64_t* schedule(uint64_t* rsp) {
    if (!is_initialized() || !is_inside_process_boundaries(rsp)) return rsp;
    running_pcb->rsp = rsp; // Lo dejamos con el RSP donde me lo haya dejado

    TPCB* next = (TPCB*) dequeue(pcb_readies_queue);
    if (next == NULL) {
        return pcb_array[0]->rsp;
    }

    if (running_pcb->state == RUNNING && count_occurrences(pcb_readies_queue, running_pcb) == 0) {
        for (uint8_t i = running_pcb->priority; i > 0; i--) {
            enqueue(pcb_readies_queue, running_pcb);
        }
    }
    if(running_pcb->state != ZOMBIE && running_pcb->state != BLOCKED) running_pcb->state = READY;
    next->state = RUNNING;
    running_pcb = next;
    return running_pcb->rsp;
}

uint8_t get_current_pid(void) {
    if (running_pcb == NULL) return 0;
    return running_pcb->pid;
}

TPCB* get_running_pcb(void) {
    return running_pcb;
} 

TPCB* get_pcb_by_pid(uint8_t pid) {
    for(int i = 0; i <= max_pid; i++) {
        if (pcb_array[i] != NULL && pcb_array[i]->pid == pid) {
            return pcb_array[i];
        }
    }
    return NULL;
}

void put_children_mpid_init(uint8_t m_pid) {
    for(int i = 0; i <= max_pid; i++) {
        if (pcb_array[i] != NULL && pcb_array[i]->m_pid == m_pid) {
            pcb_array[i]->m_pid = 0;    // 0 es el pid de la nueva madre
        }
    }
}

void put_children_zombie(uint8_t m_pid) {
    for(int i = 0; i <= max_pid; i++) {
        if (pcb_array[i] != NULL && pcb_array[i]->m_pid == m_pid) {
            pcb_array[i]->state = ZOMBIE;
        }
    }
}

void remove_pcb_from_queue(TPCB* pcb) {
    while ((dequeue_value(pcb_readies_queue, pcb)) != NULL);
}