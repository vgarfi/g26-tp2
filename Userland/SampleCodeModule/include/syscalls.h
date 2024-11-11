/**
 * @file syscalls.h
 * @brief Definition of system call functions and related constants.
 */

#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>
#include <utils.h>

/**
 * @brief Writes data to a file descriptor.
 *
 * @param fd The file descriptor to write to.
 * @param buffer The buffer containing the data to write.
 * @param len The number of bytes to write.
 * @param hexColor The color of the text in hexadecimal.
 * @return The number of bytes written, or -1 on failure.
 */
int sysWrite(uint64_t fd, unsigned char* buffer, uint64_t len, uint64_t hexColor);

/**
 * @brief Reads data from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to store the read data.
 * @param len The number of bytes to read.
 * @return The number of bytes read, or -1 on failure.
 */
int sysRead(uint64_t fd, unsigned char* buffer, uint64_t len);

/**
 * @brief Reads data from a file descriptor without blocking.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to store the read data.
 * @param len The number of bytes to read.
 * @return The number of bytes read, or -1 on failure.
 */
int sysReadNoBlock(uint64_t fd, unsigned char* buffer, uint64_t len);

/**
 * @brief Sleeps for a specified duration.
 *
 * @param secs The number of seconds to sleep.
 * @param ms The number of milliseconds to sleep.
 */
void sysSleep(uint64_t secs, uint64_t ms);

/**
 * @brief Clears the screen.
 *
 * @return 0 on success, -1 on failure.
 */
int sysClearScreen(void);

/**
 * @brief Clears the keyboard entry buffer.
 *
 * @return 0 on success, -1 on failure.
 */
int sysClearKbEntry(void);

/**
 * @brief Checks if the control key is pressed.
 *
 * @return 1 if the control key is pressed, 0 otherwise.
 */
int sysCtrlPressed(void);

/**
 * @brief Gets the value of the up arrow key.
 *
 * @return The value of the up arrow key.
 */
uint8_t sysUpArrowValue(void);

/**
 * @brief Gets the value of the left arrow key.
 *
 * @return The value of the left arrow key.
 */
uint8_t sysLeftArrowValue(void);

/**
 * @brief Gets the value of the down arrow key.
 *
 * @return The value of the down arrow key.
 */
uint8_t sysDownArrowValue(void);

/**
 * @brief Gets the value of the right arrow key.
 *
 * @return The value of the right arrow key.
 */
uint8_t sysRightArrowValue(void);

/**
 * @brief Prints a rectangle on the screen.
 *
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param base The base length of the rectangle.
 * @param height The height of the rectangle.
 * @param hexColor The color of the rectangle in hexadecimal.
 * @return 0 on success, -1 on failure.
 */
int sysPrintRectangle(int x, int y, int base, int height, uint32_t hexColor);

/**
 * @brief Prints a square on the screen.
 *
 * @param x The x-coordinate of the square.
 * @param y The y-coordinate of the square.
 * @param side The side length of the square.
 * @param hexColor The color of the square in hexadecimal.
 * @return 0 on success, -1 on failure.
 */
int sysPrintSquare(int x, int y, int side, uint32_t hexColor);

/**
 * @brief Sets the cursor position.
 *
 * @param x The x-coordinate of the cursor.
 * @param y The y-coordinate of the cursor.
 * @return 0 on success, -1 on failure.
 */
int sysSetCursorPosition(uint64_t x, uint64_t y);

/**
 * @brief Generates a beep sound from the speaker.
 *
 * @param ms The duration of the sound in milliseconds.
 * @param freq The frequency of the sound in Hertz.
 * @return 0 on success, -1 on failure.
 */
int sysBeepSound(uint64_t ms, uint64_t freq);

/**
 * @brief Gets the current seconds.
 *
 * @return The current seconds.
 */
int sysGetSecs(void);

/**
 * @brief Gets the current minutes.
 *
 * @return The current minutes.
 */
int sysGetMins(void);

/**
 * @brief Gets the current hour.
 *
 * @return The current hour.
 */
int sysGetHour(void);

/**
 * @brief Gets the current day.
 *
 * @return The current day.
 */
int sysGetDay(void);

/**
 * @brief Gets the current month.
 *
 * @return The current month.
 */
int sysGetMonth(void);

/**
 * @brief Gets the current year.
 *
 * @return The current year.
 */
int sysGetYear(void);

/**
 * @brief Zooms in the display.
 *
 * @return 0 on success, -1 on failure.
 */
int sysZoomIn(void);

/**
 * @brief Zooms out the display.
 *
 * @return 0 on success, -1 on failure.
 */
int sysZoomOut(void);

/**
 * @brief Gets the current zoom level.
 *
 * @return The current zoom level.
 */
int sysGetZoomLevel(void);

/**
 * @brief Sets the zoom level.
 *
 * @param zoom_level The zoom level to set.
 * @return 0 on success, -1 on failure.
 */
int sysSetZoomLevel(int zoom_level);

/**
 * @brief Prints the current state of the registers.
 *
 * @return 0 on success, -1 on failure.
 */
int sysPrintRegs(void);

/**
 * @brief Prints the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sysPrintCursor(void);

/**
 * @brief Hides the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sysHideCursor(void);

/**
 * @brief Shows the cursor.
 *
 * @return 0 on success, -1 on failure.
 */
int sysShowCursor(void);

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
int sysCreateProcess(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), TScope scope);

/**
 * @brief Gets the PID of the current process.
 *
 * @return The PID of the current process.
 */
uint8_t sysGetCurrentPid(void);

/**
 * @brief Exits the current process.
 *
 * @return 0 on success, -1 on failure.
 */
int sysExit(void);

/**
 * @brief Blocks a process.
 *
 * @param pid The PID of the process to block.
 * @return 0 on success, -1 on failure.
 */
int sysBlockProcess(uint8_t pid);

/**
 * @brief Unblocks a process.
 *
 * @param pid The PID of the process to unblock.
 * @return 0 on success, -1 on failure.
 */
int sysUnblockProcess(uint8_t pid);

/**
 * @brief Kills a process.
 *
 * @param pid The PID of the process to kill.
 * @return 0 on success, -1 on failure.
 */
int sysKillProcess(uint8_t pid);

/**
 * @brief Gets the scope of a process.
 *
 * @param pid The PID of the process.
 * @return The scope of the process.
 */
int sysGetScope(uint8_t pid);

/**
 * @brief Changes the priority of a process.
 *
 * @param pid The PID of the process.
 * @param newPriority The new priority of the process.
 * @return 0 on success, -1 on failure.
 */
int sysNice(uint8_t pid, uint8_t newPriority);

/**
 * @brief Prints information about all processes.
 */
void sysPs(void);

/**
 * @brief Allocates memory.
 *
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory, or NULL on failure.
 */
void* sysMalloc(uint64_t size);

/**
 * @brief Frees allocated memory.
 *
 * @param ptr The pointer to the memory to free.
 */
void sysFree(void* ptr);

/**
 * @brief Prints a memory diagnostic.
 */
void sysMem(void);

/**
 * @brief Waits for a process to finish by its PID.
 *
 * @param pid The PID of the process to wait for.
 */
void sysWaitPid(uint8_t pid);

/**
 * @brief Yields the CPU to another process.
 *
 * @return 0 on success, -1 on failure.
 */
int sysYield(void);

/**
 * @brief Creates a new semaphore.
 *
 * @param name The name of the semaphore.
 * @param initial_value The initial value of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sysCreateSem(char* name, uint64_t initial_value);

/**
 * @brief Gets a semaphore by its name.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sysGetSem(char* name);

/**
 * @brief Posts (increments) a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sysPostSem(char* name);

/**
 * @brief Waits (decrements) a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sysWaitSem(char* name);

/**
 * @brief Closes a semaphore.
 *
 * @param name The name of the semaphore.
 * @return 0 on success, -1 on failure.
 */
int sysCloseSem(char* name);

/**
 * @brief Creates a new pipe.
 *
 * @param fds The file descriptors for the pipe.
 * @param name The name of the pipe.
 * @return 0 on success, -1 on failure.
 */
int sysCreatePipe(int* fds, char* name);

/**
 * @brief Sets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int sysSetReadFileDescriptor(uint8_t pid, int fd);

/**
 * @brief Sets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @param fd The file descriptor to set.
 * @return 0 on success, -1 on failure.
 */
int sysSetWriteFileDescriptor(uint8_t pid, int fd);

/**
 * @brief Closes a pipe.
 *
 * @param name The name of the pipe.
 * @return 0 on success, -1 on failure.
 */
int sysClosePipe(char* name);

/**
 * @brief Gets the read file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The read file descriptor.
 */
int sysGetReadFileDescriptor(uint8_t pid);

/**
 * @brief Gets the write file descriptor for a process.
 *
 * @param pid The PID of the process.
 * @return The write file descriptor.
 */
int sysGetWriteFileDescriptor(uint8_t pid);

#endif