/**
 * @file loop.h
 * @brief Definition of the loop process function and related constants.
 */

#include <stdint.h>

#ifndef __LOOP_H__
#define __LOOP_H__

#define LOOP   "loop"  /**< Command name for the loop process */

/**
 * @brief Executes the loop process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t loopProcess(int argc, char** argv);

#endif