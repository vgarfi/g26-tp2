/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#include <process/process.h>
#include "../include/structures/queueADT.h"

#ifndef scheduler_H
#define scheduler_H


typedef enum {
    BLOCKED,
    READY,
    RUNNING,
    KILLED,
} TState;

typedef struct TPCB {
    uint8_t pid;        // Nuestra maxima cantidad de procesos es 256
    uint8_t m_pid;      // Mother PID
    char* name;
    TState state;
    uint64_t* rsp;
    uint8_t priority;
} TPCB;

TQueueADT pcb_readies_queue;

TPCB* running_pcb;

void add_pcb(char* name, uint64_t argc, char *argv[], void* stack_base, uint8_t pid, uint8_t priority);
uint64_t* schedule();
uint8_t get_current_pid();

#endif