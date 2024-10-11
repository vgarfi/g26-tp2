/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <memory/memoryManagerADT.h>

#define MAX_PROCESSES       1024
#define STACK_SIZE          128
#define PROCESS_SIZE        1024

#define AVAILABLE_PID       0
#define NOT_AVAILABLE_PID   1

int get_available_pid(void);
void add_pcb(char* name, uint64_t argc, char *argv[], uint64_t* stack_limit, uint64_t* stack_base, uint8_t pid, uint8_t priority, uint64_t* code);
int create_process (char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**));
uint64_t * create_initial_stack(uint64_t * stack_base, uint64_t argc, char* argv[], int64_t (*code)(int, char**), void* wrapper);

void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**));

int kill_process(uint8_t pid);

typedef struct TStackFrame {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
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
#endif