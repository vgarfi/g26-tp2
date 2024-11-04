/**
 * @file scheduled.h
 * @brief Definición del scheduler.
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

typedef struct TCodeFrame {
    uint64_t argc;
    char** argv;
    int64_t(*code)(int, char**);
} TCodeFrame;

int64_t init_process(int argc, char** argv);
int64_t idle_process(int argc, char** argv);

int get_available_pid(void);
void add_pcb(char* name, uint64_t argc, char *argv[], char* stack_limit, char* stack_base, uint8_t pid, uint8_t priority, int64_t (*code)(int, char**));
int create_process (char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**));
int block_process(uint8_t pid);
int unblock_process(uint8_t pid);
int forced_kill_process(uint8_t pid);
int change_priority(uint8_t pid, uint8_t new_priority);

void create_initial_stack(TStackFrame* stack_initial_data, char* stack_base, uint64_t argc, uint64_t argv, int64_t (*code)(int, char**));
void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**));

int kill_process(uint8_t pid);

void wait_process_by_pid(uint8_t pid);
int yield_process(void);

int processes_information(void);

int set_read_filedescriptor(uint8_t pid, int fd);
int set_write_filedescriptor(uint8_t pid, int fd);
int get_read_filedescriptor(uint8_t pid);
int get_write_filedescriptor(uint8_t pid);

#endif