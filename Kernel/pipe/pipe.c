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
    available_pipes[pipe_index] = PIPE_UNAVAILABLE;

    new_pipe->fd_r = pipe_index/2;
    new_pipe->fd_w = pipe_index/2 + 1;

    char sem_name_r[3], sem_name_w[3];
    char pipe_name_r[10], pipe_name_w[10];

    itoa(pipe_index/2, sem_name_r, 10);
    strconcat(pipe_name_r, "pipe_r_", sem_name_r);
    new_pipe->sem_r = create_sem(sem_name_r, 1);

    itoa((pipe_index/2 + 1), sem_name_w, 10);
    strconcat(pipe_name_w, "pipe_w_", sem_name_w);
    new_pipe->sem_w = create_sem(pipe_name_w, 1);
}
