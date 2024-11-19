/**
 * @file syscallDispatcher.h
 * @brief Definition of system call handlers and related functions.
 */

#ifndef __SYSCALLHANDLE_H_
#define __SYSCALLHANDLE_H_

#include <stdint.h>
#include <scheduler/scheduler.h>

// Cursor management
/**
 * @brief Sets the cursor position.
 *
 * @param x The x-coordinate of the cursor.
 * @param y The y-coordinate of the cursor.
 * @return 0 on success, -1 on failure.
 */
int sys_set_cursor(uint64_t x, uint64_t y);

/**
 * @brief Hides the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_hide_cursor(void);

/**
 * @brief Shows the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_show_cursor(void);

/**
 * @brief Prints the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_print_cursor(void);

// Arrow key values
/**
 * @brief Gets the value of the up arrow key.
 *
 * @return The value of the up arrow key.
 */
int sys_up_arrow_value(void);

/**
 * @brief Gets the value of the left arrow key.
 *
 * @return The value of the left arrow key.
 */
int sys_left_arrow_value(void);

/**
 * @brief Gets the value of the down arrow key.
 *
 * @return The value of the down arrow key.
 */
int sys_down_arrow_value(void);

/**
 * @brief Gets the value of the right arrow key.
 *
 * @return The value of the right arrow key.
 */
int sys_right_arrow_value(void);

// Screen drawing
/**
 * @brief Prints a rectangle on the screen.
 *
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param base The base length of the rectangle.
 * @param height The height of the rectangle.
 * @param hex_color The color of the rectangle in hexadecimal.
 * @return 0 on success, -1 on failure.
 */
int sys_print_rect(int x, int y, int base, int height, uint32_t hex_color);

/**
 * @brief Prints a square on the screen.
 *
 * @param x The x-coordinate of the square.
 * @param y The y-coordinate of the square.
 * @param side The side length of the square.
 * @param hex_color The color of the square in hexadecimal.
 * @return 0 on success, -1 on failure.
 */
int sys_print_square(int x, int y, int side, uint32_t hex_color);

// Screen management
/**
 * @brief Clears the screen.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_clear_screen(void);

/**
 * @brief Sleeps for a specified number of milliseconds.
 *
 * @param secs The number of seconds to sleep.
 * @param ticks The number of ticks to sleep.
 * @return 0 on success, -1 on failure.
 */
int sys_ms_sleep(uint64_t secs, uint64_t ticks);

/**
 * @brief Prints the current state of the registers.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_print_regs(void);

// Sound management
/**
 * @brief Generates a sound from the speaker.
 *
 * @param ms The duration of the sound in milliseconds.
 * @param freq The frequency of the sound in Hertz.
 * @return 0 on success, -1 on failure.
 */
int sys_sound(uint64_t ms, uint64_t freq);

// Time management
/**
 * @brief Gets the current seconds.
 *
 * @return The current seconds.
 */
int sys_get_current_seconds(void);

/**
 * @brief Gets the current minutes.
 *
 * @return The current minutes.
 */
int sys_get_current_minutes(void);

/**
 * @brief Gets the current hours.
 *
 * @return The current hours.
 */
int sys_get_current_hours(void);

/**
 * @brief Gets the current day.
 *
 * @return The current day.
 */
int sys_get_current_day(void);

/**
 * @brief Gets the current month.
 *
 * @return The current month.
 */
int sys_get_current_month(void);

/**
 * @brief Gets the current year.
 *
 * @return The current year.
 */
int sys_get_current_year(void);

// Zoom management
/**
 * @brief Increases the zoom level.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_inc_size(void);

/**
 * @brief Decreases the zoom level.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_dec_size(void);

/**
 * @brief Gets the current zoom level.
 *
 * @return The current zoom level.
 */
int sys_get_zoom_level(void);

/**
 * @brief Sets the zoom level.
 *
 * @param zoom_level The zoom level to set.
 * @return 0 on success, -1 on failure.
 */
int sys_set_zoom_level(int zoom_level);

// I/O operations
/**
 * @brief Reads from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @param buf The buffer to store the read data.
 * @param count The number of bytes to read.
 * @return The number of bytes read, or -1 on failure.
 */
int sys_read(uint64_t fd, char *buf, uint64_t count);

/**
 * @brief Reads from a file descriptor without blocking the process.
 *
 * @param fd The file descriptor to read from.
 * @param buf The buffer to store the read data.
 * @param count The number of bytes to read.
 * @return The number of bytes read, or -1 on failure.
 */
int sys_read_no_block(uint64_t fd, char *buf, uint64_t count);

/**
 * @brief Writes to a file descriptor.
 *
 * @param fd The file descriptor to write to.
 * @param buf The buffer containing the data to write.
 * @param count The number of bytes to write.
 * @param hex_color The color of the text in hexadecimal.
 * @return The number of bytes written, or -1 on failure.
 */
int sys_write(uint64_t fd, char *buf, uint64_t count, uint64_t hex_color);

// Keyboard buffer management
/**
 * @brief Cleans the keyboard buffer.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_clean_kb_buffer(void);

/**
 * @brief Checks if the control key is pressed.
 *
 * @return 1 if the control key is pressed, 0 otherwise.
 */
int sys_is_ctrl_pressed(void);

// Process management
/**
 * @brief Gets the PID of the current process.
 *
 * @return The PID of the current process.
 */
int sys_get_current_pid(void);

/**
 * @brief Exits the current process.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_exit_process(void);

/**
 * @brief Creates a new process.
 *
 * @param name The name of the process.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param code The code function of the process.
 * @param scope The scope of the process.
 * @return The PID of the created process, or -1 on failure.
 */
int sys_create_process(char *name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), TScope scope);

/**
 * @brief Blocks a process.
 *
 * @param pid The PID of the process to block.
 * @return 0 on success, -1 on failure.
 */
int sys_block_process(uint8_t pid);

/**
 * @brief Unblocks a process.
 *
 * @param pid The PID of the process to unblock.
 * @return 0 on success, -1 on failure.
 */
int sys_unblock_process(uint8_t pid);

/**
 * @brief Kills a process.
 *
 * @param pid The PID of the process to kill.
 * @return 0 on success, -1 on failure.
 */
int sys_kill_process(uint8_t pid);

/**
 * @brief Gets the scope of a process.
 *
 * @param pid The PID of the process.
 * @return The scope of the process.
 */
int sys_get_scope(uint8_t pid);

/**
 * @brief Changes the priority of a process.
 *
 * @param pid The PID of the process.
 * @param new_priority The new priority of the process.
 * @return 0 on success, -1 on failure.
 */
int sys_nice(uint8_t pid, uint8_t new_priority);

/**
 * @brief Prints information about all processes.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_ps(void);

/**
 * @brief Waits for a process to finish by its PID.
 *
 * @param pid The PID of the process to wait for.
 * @return 0 on success, -1 on failure.
 */
int sys_wait_pid(uint8_t pid);

/**
 * @brief Yields the CPU to another process.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_yield(void);

// Memory management
/**
 * @brief Allocates memory.
 *
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory, or NULL on failure.
 */
void* sys_memory_malloc(uint64_t size);

/**
 * @brief Frees allocated memory.
 *
 * @param size The pointer to the memory to free.
 * @return 0 on success, -1 on failure.
 */
int sys_memory_free(void* size);

/**
 * @brief Gets the status of the memory.
 *
 * @return 0 on success, -1 on failure.
 */
int sys_memory_status(void);

// Semaphore management
/**
 * @brief Creates a new semaphore.
 *
 * @param name The name of the semaphore.
 * @param initial_value The initial value of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sys_create_sem(char* name, uint64_t initial_value);

/**
 * @brief Gets a semaphore by its name.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sys_get_sem(char* name);

/**
 * @brief Posts (increments) a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sys_post_sem(char* name);

/**
 * @brief Waits (decrements) a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sys_wait_sem(char* name);

/**
 * @brief Closes a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sys_close_sem(char* name);

// Pipe management
/**
 * @brief Creates a new pipe.
 *
 * @param fds The file descriptors for the pipe.
 * @param name The name of the pipe.
 * @return 0 on success, -1 on failure.
 */
int sys_create_pipe(int* fds, char* name);

/**
 * @brief Sets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int sys_set_read_file_descriptor(uint8_t pid, int fd);

/**
 * @brief Sets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int sys_set_write_file_descriptor(uint8_t pid, int fd);

/**
 * @brief Gets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The read file descriptor.
 */
int sys_get_read_file_descriptor(uint8_t pid);

/**
 * @brief Gets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The write file descriptor.
 */
int sys_get_write_file_descriptor(uint8_t pid);
void* sys_get_shared_memory(uint8_t id);
#endif