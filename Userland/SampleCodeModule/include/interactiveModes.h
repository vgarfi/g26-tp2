/**
 * @file interactiveModes.h
 * @brief Definition of functions for handling interactive modes in the shell.
 */

#ifndef MODES_H
#define MODES_H

#include <processModes.h>
#include <eliminatorGame.h>
#include <syscalls.h>
#include <testProc.h>
#include <testSync.h>
#include <testMm.h>
#include <loop.h>
#include <utils.h>
#include <phylo.h>
#include <ipc.h>
#include <stdio.h>
#include "shell.h"

/**
 * @brief Processes a command with pipes.
 *
 * @param input The command input containing pipes.
 */
void pipeProcesses(char* input);

/**
 * @brief Creates a background process.
 *
 * @param input The command input to create the background process.
 */
void createBackgroundProcess(char* input);

#endif