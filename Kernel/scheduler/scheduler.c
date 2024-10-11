#include <kernelManagement.h>
#include <videoDriver.h>
#include <scheduler/scheduler.h>

extern TPCB* pcb_array[MAX_PROCESSES];

TQueueADT pcb_readies_queue;
TPCB* running_pcb;

int is_initialized(void){
    return pcb_array[0] != NULL;
}

int is_inside_process_boundaries(uint64_t* rsp) {
    return (rsp >= running_pcb->stack_limit && rsp <= running_pcb->stack_base);
}

uint64_t* schedule(uint64_t* rsp) {
    if(pcb_array[0] == NULL) return rsp;
    return pcb_array[0]->rsp;
    //if (!is_initialized() || !is_inside_process_boundaries(rsp)) return rsp;
    //running_pcb->rsp = rsp;
    //return rsp;

    // char buffer[50];
    // itoa(rsp, buffer, 10);
    // vdPrint("\nSCHEDULE->RSP: ", 0x00FFFFFF);
    // vdPrint(buffer, 0x00FFFFFF);

    // TPCB* next = (TPCB*) dequeue(pcb_readies_queue);
    // if (next == NULL) {
    //     return pcb_array[0]->rsp;
    // }

    // if (running_pcb->state == RUNNING) {
    //     running_pcb->state = READY;
    //     for (uint8_t i = running_pcb->priority; i > 0; i--) {
    //         enqueue(pcb_readies_queue, running_pcb); // cuando en la syscall de kill se mata a un proceso hay qye borrarlo de la queue priority veces
    //     }
    // }
    
    // next->state = RUNNING;
    // running_pcb = next;
    // vdPrint("\nRUNNING_PCB pasa a ser: ", 0x00FFFFFF);
    // itoa(running_pcb->rsp, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);

    // return running_pcb->rsp;
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