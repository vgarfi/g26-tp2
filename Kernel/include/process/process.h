/**
 * @file scheduled.h
 * @brief Definición del scheduler.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <memory/memoryManagerADT.h>
#define MAX_PROCESSES   1024

uint8_t create_process (char* name, uint64_t argc, char *argv[], uint8_t priority, int64_t (*code)(int, char**));
uint64_t * create_initial_stack(uint64_t * stack_base, uint64_t argc, char* argv[], int64_t (*code)(int, char**), void* wrapper);

void wrapper(uint64_t argc, char* argv[], int64_t (*code)(int, char**));
TPCB* pcb_array[MAX_PROCESSES];

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
} TStackFrame;

typedef struct TCodeFrame {
    uint64_t argc;
    char** argv;
    int64_t(*code)(int, char**);
} TCodeFrame;
#endif