#ifndef STACK_H
#define STACK_H

#include <cstdint>

#define STACK_SIZE     128

typedef struct TStack {
    uint64_t* base;
    uint64_t* current;
} TStack;

#endif