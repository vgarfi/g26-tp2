/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#include <process/process.h>
#include "string.h"
#include "../include/structures/queueADT.h"

#ifndef scheduler_H
#define scheduler_H


typedef enum {
    BLOCKED,
    READY,
    RUNNING,
    KILLED,     // Sabemos que killed y zombie no son estados de procesos
    ZOMBIE,     // pero esto nos permite conocer características de los mismos de una manera organizada
} TState;

typedef struct TPCB {
    uint8_t pid;        // Nuestra maxima cantidad de procesos es 256
    uint8_t m_pid;      // Mother PID
    char* name;
    TState state;
    uint64_t* rsp;
    uint8_t priority;
} TPCB;

extern TPCB* pcb_array[MAX_PROCESSES];

extern TQueueADT pcb_readies_queue;

extern TPCB* running_pcb;

uint64_t* schedule();
uint8_t get_current_pid();
TPCB* get_pcb_by_pid(uint8_t pid);
void kill_pcb(TPCB* pcb);
void put_children_zombie(uint8_t m_pid);
#endif