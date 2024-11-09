/**
 * @file pipe.h
 * @brief Definition of the Pipe structure and related functions for pipe management.
 */

#ifndef pipe_H
#define pipe_H

#include <synchro/synchro.h>

#define MAX_BUFFER_SIZE     256
#define MAX_PIPES           256
#define PIPE_AVAILABLE      1
#define PIPE_UNAVAILABLE    0

#define EOF                 -1

typedef struct pipe {
    char* name;
    int fd_r;
    int fd_w;
    char buffer[MAX_BUFFER_SIZE];
    TSemaphore* sem_r;
    TSemaphore* sem_w;
    int read_cursor_index;      // Index of the last character read
    int write_cursor_index;     // Index of the last character written
    char eof_flag;
} TPipe;

extern TPipe* pipes[MAX_PIPES];
extern int available_pipes[MAX_PIPES];

/**
 * @brief Initializes the pipe system.
 */
void initialize_pipes(void);

/**
 * @brief Creates a new pipe.
 *
 * @param fds Array to store the file descriptors for reading and writing.
 * @param name Name of the pipe.
 * @return pipe index on success, -1 on failure.
 */
int create_pipe(int* fds, char* name);

/**
 * @brief Checks if a pipe is anonymous.
 *
 * @param pipe_index Index of the pipe.
 * @return 1 if the pipe is anonymous, 0 otherwise.
 */
char is_anonymous_pipe(int pipe_index);

/**
 * @brief Reads data from a pipe.
 *
 * @param pipe_index Index of the pipe.
 * @param buf Buffer to store the read data.
 * @param count Number of bytes to read.
 * @return Number of bytes read, or -1 on failure.
 */
int read_pipe(int pipe_index, char * buf, uint64_t count);

/**
 * @brief Writes data to a pipe.
 *
 * @param pipe_index Index of the pipe.
 * @param buf Buffer containing the data to write.
 * @param count Number of bytes to write.
 * @return Number of bytes written, or -1 on failure.
 */
int write_pipe(int pipe_index, char * buf, uint64_t count);

/**
 * @brief Marks a pipe as finished.
 *
 * @param pipe_index Index of the pipe.
 * @return 0 on success, -1 on failure.
 */
int finish_pipe(int pipe_index);

/**
 * @brief Closes a pipe.
 *
 * @param pipe_index Index of the pipe.
 * @return 0 on success, -1 on failure.
 */
int close_pipe(int pipe_index);

/**
 * @brief Frres a pipe.
 *
 * @param pipe_index Index of the pipe.
 * @return 0 on success, -1 on failure.
 */
int free_pipe(int pipe_index);

#endif