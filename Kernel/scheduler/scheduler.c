#include <kernelManagement.h>
#include <scheduler/scheduler.h>
#include <videoDriver.h>

extern TPCB* pcb_array[MAX_PROCESSES];

void failure_scheduling(void);

TQueueADT pcb_readies_queue;
TPCB* running_pcb;

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
        failure_scheduling();
        return pcb_array[0]->rsp;
    }

    if (running_pcb->state == RUNNING && count_occurrences(pcb_readies_queue, running_pcb) == 0) {
        running_pcb->state = READY;
        for (uint8_t i = running_pcb->priority; i > 0; i--) {
            enqueue(pcb_readies_queue, running_pcb); // cuando en la syscall de kill se mata a un proceso hay qye borrarlo de la queue priority veces
        }
    }
    
    next->state = RUNNING;
    running_pcb = next;
    return running_pcb->rsp;
}


void failure_scheduling(void){

}

uint8_t get_current_pid() {
    if (running_pcb == NULL) return 0;
    return running_pcb->pid;    
}

TPCB* get_pcb_by_pid(uint8_t pid) {
    for(int i = 0; i < MAX_PROCESSES; i++){
        if (pcb_array[i]->pid == pid) {
            return pcb_array[i];
        }
    }
    return NULL;
}

void put_children_zombie(uint8_t m_pid) {
    for(int i = 0; i < MAX_PROCESSES; i++) {
        if (pcb_array[i]->m_pid == m_pid) {
            pcb_array[i]->state = ZOMBIE;
        }
    }
}

void kill_pcb(TPCB* pcb) {
    if (pcb->state == READY || pcb->state == RUNNING) {
        while((dequeue_value(pcb_readies_queue, pcb)) != NULL); // Lo eliminamos de la lista las veces necesarias
        if (pcb->state == RUNNING) {
            //timer_interrupt(); // TODO llamar a la interrupción del timer
        }
    }
    put_children_zombie(pcb->pid);
    pcb->state = KILLED;
}