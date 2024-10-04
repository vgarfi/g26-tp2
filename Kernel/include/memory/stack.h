#include <cstdint>

#define STACK_SIZE     128

typedef struct TStack {
    uint64_t* base;
    uint64_t* current;
} TStack;