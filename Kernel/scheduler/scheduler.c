#include <scheduler/scheduler.h>
#include <kernel.c> // TODO mover a un .h

uint64_t* schedule(){
    TPCB* next = (TPCB*) dequeue(pcb_readies_queue);
    if (next == NULL) {
        return pcb_array[0]->rsp;
    }

    if (running_pcb->state == RUNNING){
        running_pcb->state = READY;
        
        for (uint8_t i = running_pcb->priority; i > 0; i--) {
            enqueue(pcb_readies_queue, running_pcb); // cuando en la syscall de kill se mata a un proceso hay qye borrarlo de la queue priority veces
        }
    }
    next->state = RUNNING;
    running_pcb = next;  
}

uint8_t get_current_pid() {
    if (running_pcb == NULL) return 0;
    return running_pcb->pid;    
}

TPCB* get_pcb_by_pid(uint8_t pid) {
    for(int i = 0; i < MAX_PROCESSES-1; i++){
        if (pcb_array[i]->pid == pid) {
            return pcb_array[i];
        }
    }
    return NULL;
}

void remove_pcb(TPCB* pcb){
    dequeue_value(pcb_readies_queue, pcb);
    free_mm(memory_manager, pcb->rsp);
    free_mm(memory_manager, pcb->name);
    free_mm(memory_manager, pcb);
}

