#ifndef pipe_H
#define pipe_H

#include <synchro/synchro.h>

#define MAX_BUFFER_SIZE     2048
#define MAX_PIPES           256
#define PIPE_AVAILABLE      1
#define PIPE_UNAVAILABLE    0

typedef struct pipe {
    char* name;
    int fdr;
    int fdw;
    char buffer[MAX_BUFFER_SIZE];
    TSemaphore* semr;
    TSemaphore* semw;
} TPipe;

extern TPipe* pipes[MAX_PIPES];
extern int available_pipes[MAX_PIPES];

void initialize_pipes(void);
int create_pipe(char* name);

#endif