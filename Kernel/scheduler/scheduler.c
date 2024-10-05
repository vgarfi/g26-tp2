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