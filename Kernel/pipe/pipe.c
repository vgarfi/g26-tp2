#include <pipe/pipe.h>
#include <string.h>
#include <synchro/synchro.h>
#include <memory/memoryManagerADT.h>

extern MemoryManagerADT memory_manager;

TPipe* pipes[MAX_PIPES];
int available_pipes[MAX_PIPES];

void initialize_pipes(){
    for(int i = 0; i < MAX_PIPES; i++){
        available_pipes[i] = PIPE_AVAILABLE;
    }
}

int getFreePipeIndex() {
    for(int i = 0; i < MAX_PIPES; i++){
        if(available_pipes[i] == PIPE_AVAILABLE)
            return i;
    }
}

int create_pipe(char* name){
    TPipe* new_pipe = (TPipe*)malloc_mm(memory_manager, sizeof(TPipe));
    if(new_pipe == NULL)
        return -1;

    new_pipe->name = malloc_mm(memory_manager, strlen(name) + 1);
    if(new_pipe->name == NULL){
        free_mm(memory_manager, new_pipe);
        return -1;
    }
    strcpy(new_pipe->name, name);

    int pipe_index = getFreePipeIndex();

    pipes[pipe_index] = new_pipe;

    new_pipe->fdr = pipe_index/2;
    new_pipe->fdr = pipe_index/2 + 1;

    char sem_name[10];

    itoa(pipe_index/2, sem_name, 10);
    new_pipe->semr = create_sem(sem_name, 1);

    itoa(pipe_index/2 + 1, sem_name, 10);
    new_pipe->semw = create_sem(sem_name, 1);
}
