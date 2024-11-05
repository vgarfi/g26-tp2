/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#include <process/process.h>
#include <synchro/synchro.h>
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

enum {
    FOREGROUND,
    BACKGROUND
};

typedef int TScope;

typedef struct TPCB {
    uint8_t pid;        // Nuestra maxima cantidad de procesos es 256
    uint8_t m_pid;      // Mother PID
    char* name;
    TState state;
    uint64_t* stack_limit;
    uint64_t* stack_base;
    uint64_t* rsp;
    uint8_t priority;
    TSemaphore* semaphore;
    int fd_r;
    int fd_w;
    TScope scope;
} TPCB;

extern TPCB* pcb_array[MAX_PROCESSES];

extern TQueueADT pcb_readies_queue;

extern TPCB* running_pcb;

void initialize_scheduling(void);
int is_initialized(void);
int is_inside_process_boundaries(uint64_t* rsp);
uint64_t* schedule(uint64_t* rsp);
uint8_t get_current_pid(void);
TPCB* get_pcb_by_pid(uint8_t pid);
TPCB* get_running_pcb(void);
void remove_pcb_from_queue(TPCB* pcb);
#endif