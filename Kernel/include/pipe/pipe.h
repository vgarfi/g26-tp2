#ifndef pipe_H
#define pipe_H

#include <synchro/synchro.h>

#define MAX_BUFFER_SIZE     2048
#define MAX_PIPES           256

typedef struct pipe {
    char* name;
    int fdr;
    int fdw;
    char buffer[MAX_BUFFER_SIZE];
    TSemaphore* semr;
    TSemaphore* semw;
} TPipe;

static TPipe pipes[MAX_PIPES];

#endif