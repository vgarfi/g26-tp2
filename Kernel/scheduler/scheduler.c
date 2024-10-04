#include "../include/scheduler/scheduler.h"
#include <kernel.c> // TODO mover a un .h

uint64_t* schedule(){
    TPCB* next = (TPCB*) dequeue(pcb_readies_queue);
    if (next == NULL) {
        return pcb_array[0]->rsp;
    }

    if (running_pcb->state == RUNNING){
        running_pcb->state = READY;
        
        for (uint8_t i = running_pcb->priority; i > 0; i--) {
            enqueue(pcb_readies_queue, running_pcb);
        }
    }
    next->state = RUNNING;
    running_pcb = next;  
}

void add_pcb(void* stack_base, uint8_t pid, uint8_t priority) {
    TPCB* new_pcb = (TPCB*) malloc_mm(memory_manager, sizeof(TPCB));
    if (new_pcb == NULL || priority == 0) {
        free_mm(memory_manager, new_pcb);
        return;
    }

    new_pcb->pid = pid;
    new_pcb->m_pid = get_current_pid();
    new_pcb->rsp = stack_base;
    new_pcb->state = READY;
    new_pcb->priority = priority;

    pcb_array[pid] = new_pcb;
    
    enqueue(pcb_readies_queue, new_pcb);
    return;
}

uint8_t get_current_pid() {
    if (running_pcb == NULL) return 0;
    return running_pcb->pid;    
}