/**
 * @file builtinModes.h
 * @brief Definition of built-in shell commands and related functions.
 */

#ifndef _BUILTIN_MODES_H
#define _BUILTIN_MODES_H

#include <dateTime.h>
#include <exceptions.h>
#include <syscalls.h>
#include <colors.h>
#include "stdio.h"
#include "shell.h"
#include <lib.h>

/**
 * @brief Displays help information for shell commands.
 */
void help(void);

/**
 * @brief Plays an Easter egg.
 */
void playEasterEgg(void);

/**
 * @brief Clears the screen.
 */
void clear(void);

/**
 * @brief Displays the current time.
 */
void time(void);

/**
 * @brief Displays the current date.
 */
void date(void);

/**
 * @brief Zooms in the display.
 */
void zoomin(void);

/**
 * @brief Zooms out the display.
 */
void zoomout(void);

/**
 * @brief Triggers a division by zero exception.
 */
void divByZero(void);

/**
 * @brief Triggers an invalid operation exception.
 */
void invalidOp(void);

/**
 * @brief Displays the current state of the registers.
 */
void registers(void);

/**
 * @brief Displays a message indicating that a command was not found.
 *
 * @param commandNotFound The command that was not found.
 */
void notFound(char* commandNotFound);

/**
 * @brief Displays the current processes statuses.
 */
void psPrinting(void);

/**
 * @brief Displays the current memory status.
 */
void mem(void);

/**
 * @brief Blocks a process.
 */
void blockp(void);

/**
 * @brief Unblocks a process.
 */
void unblockp(void);

/**
 * @brief Changes the priority of a process.
 */
void nicep(void);

/**
 * @brief Kills a process.
 */
void killp(void);

#endif