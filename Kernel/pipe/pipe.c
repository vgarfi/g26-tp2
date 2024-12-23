// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipe/pipe.h>
#include <string.h>
#include <videoDriver.h>
#include <synchro/synchro.h>
#include <memory/memoryManagerADT.h>
#include <kernelManagement.h>

extern MemoryManagerADT memory_manager;

TPipe* pipes[MAX_PIPES];
int available_pipes[MAX_PIPES];

void initialize_pipes(){
    for(int i = 0; i < MAX_PIPES; i++){
        available_pipes[i] = PIPE_AVAILABLE;
    }
}

int get_free_pipe_index() {
    for(int i = 1; i < MAX_PIPES; i++){
        if(available_pipes[i] == PIPE_AVAILABLE)
            return i;
    }
    return -1;
}

int create_pipe(int* fds, char* name){
    if (fds == NULL) {
        return -1;
    }

    TPipe* new_pipe = (TPipe*)malloc_mm(memory_manager, sizeof(TPipe));
    if(new_pipe == NULL)
        return -1;

    int pipe_name_len = strlen(name);
    if (pipe_name_len != 0) {
        new_pipe->name = malloc_mm(memory_manager, pipe_name_len + 1);
        if(new_pipe->name == NULL){
            free_mm(memory_manager, new_pipe);
            return -1;
        }
        strcpy(new_pipe->name, name);
    } else {
        new_pipe->name = NULL;
    }

    int pipe_index = get_free_pipe_index();

    if(pipe_index == -1) {
        return -1;   
    }

    pipes[pipe_index] = new_pipe;
    available_pipes[pipe_index] = PIPE_UNAVAILABLE;

    new_pipe->fd_r = pipe_index*2;
    new_pipe->fd_w = (pipe_index*2) + 1;

    fds[0] = new_pipe->fd_r;
    fds[1] = new_pipe->fd_w;

    new_pipe->read_cursor_index = 0;
    new_pipe->write_cursor_index = 0;
    new_pipe->eof_flag = 0;

    char sem_name_r[3], sem_name_w[3];
    char pipe_name_r[10], pipe_name_w[10];

    itoa(new_pipe->fd_r, sem_name_r, 10);
    strconcat(pipe_name_r, "pipe_r_", sem_name_r);
    new_pipe->sem_r = create_sem(pipe_name_r, 0);

    itoa(new_pipe->fd_w, sem_name_w, 10);
    strconcat(pipe_name_w, "pipe_w_", sem_name_w);
    new_pipe->sem_w = create_sem(pipe_name_w, MAX_BUFFER_SIZE);

    return pipe_index;
}

char is_anonymous_pipe(int pipe_index) {
    if (pipe_index == 0) {
        return 0;
    } 
    if (pipes[pipe_index] == NULL || available_pipes[pipe_index] == PIPE_AVAILABLE) {
        return 1;
    }
    return (pipes[pipe_index]->name == NULL);
}

int read_pipe(int pipe_index, char * buf, uint64_t count) {
	if (pipe_index < 0 || pipe_index >= MAX_PIPES || available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index] == NULL) {
		return 0;
	}

    TPipe* pipe = pipes[pipe_index];

    if (pipe->eof_flag == (char)EOF) {
        buf[0] = EOF;
        return EOF;
    }

    int i;
    for(i = 0; i < count; i++) {
        wait_sem(pipe->sem_r->name);
        buf[i] = pipe->buffer[pipe->read_cursor_index % MAX_BUFFER_SIZE];
        pipe->read_cursor_index++;
        post_sem(pipe->sem_w->name);
    }

    return i;
}

int write_pipe(int pipe_index, char * buf, uint64_t count) {
    if (pipe_index < 0 || pipe_index >= MAX_PIPES || available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index] == NULL) {
		return 0;
	}

    TPipe* pipe = pipes[pipe_index];

    if (pipe->eof_flag == (char)EOF) {
        return EOF;
    }

    int i;
    for (i = 0; i < count; i++){
        wait_sem(pipe->sem_w->name);
        pipe->buffer[pipe->write_cursor_index % MAX_BUFFER_SIZE] = buf[i];
        pipe->write_cursor_index++;
        post_sem(pipe->sem_r->name);
    }
    
    return i;
}

int finish_pipe(int pipe_index) {
    if (pipe_index < 0 || pipe_index >= MAX_PIPES || available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index] == NULL) {
		return -1;
	}
    delete_sem(pipes[pipe_index]->sem_r->name);
    delete_sem(pipes[pipe_index]->sem_w->name);
    pipes[pipe_index]->eof_flag = (char)EOF;
    return 0;
}

int close_pipe(int pipe_index) {
    if (pipe_index < 0 || pipe_index >= MAX_PIPES || available_pipes[pipe_index] == PIPE_AVAILABLE || pipes[pipe_index] == NULL) {
		return -1;
	}
    delete_sem(pipes[pipe_index]->sem_r->name);
    delete_sem(pipes[pipe_index]->sem_w->name);
    free_pipe(pipe_index);
    return 0;
}

int free_pipe(int pipe_index) {
    if (pipe_index < 0 || pipe_index >= MAX_PIPES || available_pipes[pipe_index] == PIPE_AVAILABLE) {
		return -1;
	}

    TPipe* pipe = pipes[pipe_index];

    if (pipe == NULL) {
        return -1;
    }

    if (pipe->name != NULL) {
        free_mm(memory_manager, pipe->name);
    }

    if (pipe->sem_r != NULL && pipe->sem_r->name != NULL) {
        delete_sem(pipe->sem_r->name);
    }
    if (pipe->sem_w != NULL && pipe->sem_w->name != NULL) {
        delete_sem(pipe->sem_w->name);
    }
    pipes[pipe_index] = NULL;
    return 0;
}