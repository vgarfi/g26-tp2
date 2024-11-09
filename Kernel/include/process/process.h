/**
 * @file process.h
 * @brief Definition of the process structure and related functions for process management.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <memory/memoryManagerADT.h>
#include <kernelManagement.h>

#define STACK_SIZE          2048

#define PROCESS_SIZE        STACK_SIZE

#define MAX_PROCESSES       (MEMORY_SIZE/PROCESS_SIZE)/1024

#define AVAILABLE_PID       0
#define NOT_AVAILABLE_PID   1

#include <scheduler/scheduler.h>

/**
 * @struct TStackFrame
 * @brief Structure representing the stack frame of a process.
 */
typedef struct TStackFrame {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
    uint64_t align;
} TStackFrame;

/**
 * @struct TCodeFrame
 * @brief Structure representing the code frame of a process.
 */
typedef struct TCodeFrame {
    uint64_t argc;
    char** argv;
    int64_t(*code)(int, char**);
} TCodeFrame;

/**
 * @brief Initializes a process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code.
 */
int64_t init_process(int argc, char** argv);

/**
 * @brief Idle process function.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code.
 */
int64_t idle_process(int argc, char** argv);

/**
 * @brief Gets an available PID.
 *
 * @return The available PID.
 */
int get_available_pid(void);

/**
 * @brief Adds a process control block (PCB).
 *
 * @param name The name of the process.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param stack_limit The stack limit.
 * @param stack_base The stack base.
 * @param pid The process ID.
 * @param priority The priority of the process.
 * @param code The code function of the process.
 * @param scope The scope of the process.
 */
void add_pcb(char* name, uint64_t argc, char *argv[], char* stack_limit, char* stack_base, uint8_t pid, uint8_t priority, int64_t (*code)(int, char**), TScope scope);

/**
 * @brief Creates a new process.
 *
 * @param name The name of the process.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param priority The priority of the process.
 * @param code The code function of the process.
 * @param scope The scope of the process.
 * @return The PID of the created process, or -1 on failure.
 */
int create_process(char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**), TScope scope);

/**
 * @brief Blocks a process.
 *
 * @param pid The PID of the process to block.
 * @return 0 on success, -1 on failure.
 */
int block_process(uint8_t pid);

/**
 * @brief Unblocks a process.
 *
 * @param pid The PID of the process to unblock.
 * @return 0 on success, -1 on failure.
 */
int unblock_process(uint8_t pid);

/**
 * @brief Forces the termination of a process.
 *
 * @param pid The PID of the process to terminate.
 * @return 0 on success, -1 on failure.
 */
int forced_kill_process(uint8_t pid);

/**
 * @brief Changes the priority of a process.
 *
 * @param pid The PID of the process.
 * @param new_priority The new priority of the process.
 * @return 0 on success, -1 on failure.
 */
int change_priority(uint8_t pid, uint8_t new_priority);

/**
 * @brief Creates the initial stack for a process.
 *
 * @param stack_initial_data The initial stack data.
 * @param stack_base The stack base.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param code The code function of the process.
 */
void create_initial_stack(TStackFrame* stack_initial_data, char* stack_base, uint64_t argc, uint64_t argv, int64_t (*code)(int, char**));

/**
 * @brief Wrapper function for process execution.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param code The code function of the process.
 */
void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**));

/**
 * @brief Terminates a process.
 *
 * @param pid The PID of the process to terminate.
 * @return 0 on success, -1 on failure.
 */
int kill_process(uint8_t pid);

/**
 * @brief Forces the termination of piped processes.
 *
 * @param fd The file descriptor of the pipe.
 */
void force_kill_piped_processes(int fd);

/**
 * @brief Waits for a process to finish by its PID.
 *
 * @param pid The PID of the process to wait for.
 */
void wait_process_by_pid(uint8_t pid);

/**
 * @brief Yields the CPU to another process.
 *
 * @return 0 on success, -1 on failure.
 */
int yield_process(void);

/**
 * @brief Gets the scope of a process.
 *
 * @param pid The PID of the process.
 * @return The scope of the process.
 */
int get_process_scope(uint8_t pid);

/**
 * @brief Prints information about all processes.
 *
 * @return 0 on success, -1 on failure.
 */
int processes_information(void);

/**
 * @brief Sets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int set_read_filedescriptor(uint8_t pid, int fd);

/**
 * @brief Sets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int set_write_filedescriptor(uint8_t pid, int fd);

/**
 * @brief Gets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The read file descriptor.
 */
int get_read_filedescriptor(uint8_t pid);

/**
 * @brief Gets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The write file descriptor.
 */
int get_write_filedescriptor(uint8_t pid);

#endif