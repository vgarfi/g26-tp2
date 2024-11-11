/**
 * @file scheduler.h
 * @brief Definition of the scheduler.
 */

#include <process/process.h>
#include <synchro/synchro.h>
#include <string.h>
#include <structures/queueADT.h>

#ifndef scheduler_H
#define scheduler_H

/**
 * @enum TState
 * @brief Enumeration of process states.
 */
typedef enum {
    BLOCKED,
    READY,
    RUNNING,
    KILLED,     // We know that killed and zombie are not process states
    ZOMBIE,     // but this allows us to know their characteristics in an organized way
} TState;

/**
 * @enum TScope
 * @brief Enumeration of process scopes.
 */
enum {
    FOREGROUND,
    BACKGROUND
};

typedef int TScope;

/**
 * @struct TPCB
 * @brief Structure representing a process control block (PCB).
 */
typedef struct TPCB {
    uint8_t pid;        // Our maximum number of processes is 256
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
    int argc;
    char** argv;
} TPCB;

extern TPCB* pcb_array[MAX_PROCESSES];

extern TQueueADT pcb_readies_queue;

extern TPCB* running_pcb;

/**
 * @brief Initializes the scheduling system.
 */
void initialize_scheduling(void);

/**
 * @brief Checks if the scheduling system is initialized.
 *
 * @return 1 if initialized, 0 otherwise.
 */
int is_initialized(void);

/**
 * @brief Checks if a given stack pointer is within process boundaries.
 *
 * @param rsp The stack pointer to check.
 * @return 1 if inside boundaries, 0 otherwise.
 */
int is_inside_process_boundaries(uint64_t* rsp);

/**
 * @brief Schedules the next process to run.
 *
 * @param rsp The current stack pointer.
 * @return The stack pointer of the next process to run.
 */
uint64_t* schedule(uint64_t* rsp);

/**
 * @brief Gets the PID of the current running process.
 *
 * @return The PID of the current running process.
 */
uint8_t get_current_pid(void);

/**
 * @brief Gets the PCB of a process by its PID.
 *
 * @param pid The PID of the process.
 * @return The PCB of the process.
 */
TPCB* get_pcb_by_pid(uint8_t pid);

/**
 * @brief Gets the PCB of the currently running process.
 *
 * @return The PCB of the currently running process.
 */
TPCB* get_running_pcb(void);

/**
 * @brief Removes a PCB from the ready queue.
 *
 * @param pcb The PCB to remove.
 */
void remove_pcb_from_queue(TPCB* pcb);

/**
 * @brief Sets the mother PID of all children processes to the init process.
 *
 * @param m_pid The mother PID.
 */
void put_children_mpid_init(uint8_t m_pid);

/**
 * @brief Sets the state of all children processes to zombie.
 *
 * @param m_pid The mother PID.
 */
void put_children_zombie(uint8_t m_pid);

#endif