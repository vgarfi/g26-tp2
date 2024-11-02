#ifndef pipe_H
#define pipe_H

#include <synchro/synchro.h>

#define MAX_BUFFER_SIZE     256
#define MAX_PIPES           256
#define PIPE_AVAILABLE      1
#define PIPE_UNAVAILABLE    0

// TODO preguntar si es correcto que las funciones y variables de kernel sean con snake_case y userland con camelCase
typedef struct pipe {
    char* name;
    int fd_r;
    int fd_w;
    char buffer[MAX_BUFFER_SIZE];
    TSemaphore* sem_r;
    TSemaphore* sem_w;
} TPipe;

extern TPipe* pipes[MAX_PIPES];
extern int available_pipes[MAX_PIPES];

void initialize_pipes(void);
int create_pipe(char* name);

#endif