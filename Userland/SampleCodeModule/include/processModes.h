/**
 * @file processModes.h
 * @brief Definition of process mode functions and related constants.
 */

#ifndef _PROCESS_MODES_H
#define _PROCESS_MODES_H

#include <eliminatorGame.h>
#include <syscalls.h>
#include <testProc.h>
#include <testSync.h>
#include <testMm.h>
#include <loop.h>
#include <utils.h>
#include <phylo.h>
#include <ipc.h>
#include "stdio.h"

/**
 * @brief Plays the Eliminator game.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int playEliminator(TScope scope);

/**
 * @brief Executes the process test.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int processTest(TScope scope);

/**
 * @brief Executes the priorities test.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int prioritiesTest(TScope scope);

/**
 * @brief Executes the memory test.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int memoryTest(TScope scope);

/**
 * @brief Executes the synchronization test.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int syncTest(TScope scope);

/**
 * @brief Executes the loop process.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int loop(TScope scope);

/**
 * @brief Executes the cat process.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int cat(TScope scope);

/**
 * @brief Executes the word count process.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int wc(TScope scope);

/**
 * @brief Executes the filter process.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int filter(TScope scope);

/**
 * @brief Executes the philosophers process.
 *
 * @param scope The scope of the process.
 * @return Status code of the process.
 */
int phylosophers(TScope scope);

#endif