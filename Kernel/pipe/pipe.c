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
    for(int i = 1; i < MAX_PIPES; i++){
        if(available_pipes[i] == PIPE_AVAILABLE)
            return i;
    }
}

int create_pipe(char* name, int* fds){
    if (fds[0] == NULL || fds[1] == NULL) {
        return -1;
    }

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

    new_pipe->fd_r = pipe_index*2;
    new_pipe->fd_w = (pipe_index*2) + 1;

    fds[0] = new_pipe->fd_r;
    fds[1] = new_pipe->fd_w;

    new_pipe->read_cursor_index = 0;
    new_pipe->write_cursor_index = 0;

    char sem_name_r[3], sem_name_w[3];
    char pipe_name_r[10], pipe_name_w[10];

    itoa( new_pipe->fd_r, sem_name_r, 10);
    strconcat(pipe_name_r, "pipe_r_", sem_name_r);
    new_pipe->sem_r = create_sem(sem_name_r, 1);

    itoa(new_pipe->fd_w, sem_name_w, 10);
    strconcat(pipe_name_w, "pipe_w_", sem_name_w);
    new_pipe->sem_w = create_sem(pipe_name_w, 1);

    return pipe_index;
}


int read_pipe(int pipe_index, char * buf, uint64_t count) {
	if (available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index]->read_cursor_index == pipes[pipe_index]->write_cursor_index) {
		return 0;
	}
    int i;
    wait_sem(pipes[pipe_index]->sem_r->name);
    for (i = 0; i < count && pipes[pipe_index]->read_cursor_index < pipes[pipe_index]->write_cursor_index && pipes[pipe_index]->read_cursor_index < MAX_BUFFER_SIZE; i++) {
        buf[i] = pipes[pipe_index]->buffer[pipes[pipe_index]->read_cursor_index++];
    }
    post_sem(pipes[pipe_index]->sem_r->name);
    return i;
}

int write_pipe(int pipe_index, char * buf, uint64_t count) {
    if (available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index]->write_cursor_index == MAX_BUFFER_SIZE) {
        return 0;
    }

    wait_sem(pipes[pipe_index]->sem_w->name);
    int i;
    for (i = 0; i < count && pipes[pipe_index]->write_cursor_index < MAX_BUFFER_SIZE; i++) {
        pipes[pipe_index]->buffer[pipes[pipe_index]->write_cursor_index++] = buf[i];
    }
    post_sem(pipes[pipe_index]->sem_w->name);
    return i;
}