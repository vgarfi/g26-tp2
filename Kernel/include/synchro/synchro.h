#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdint.h>
#include <structures/queueADT.h>

typedef struct TSemaphore {
    char* name;
    uint64_t value;
    uint8_t lock;
    TQueueADT waiting_processes;
} TSemaphore;

char initialize_synchro(void);
TSemaphore* create_sem(char* name, uint64_t initial_value);
TSemaphore* get_sem(char* name);
void wait_sem(char* name);
void post_sem(char* name);
void delete_sem(char* name);
#endif