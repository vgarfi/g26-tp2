/**
 * @file ps.h
 * @brief Definition of the ps process function and related constants.
 */

#ifndef __PS_H__
#define __PS_H__

#include <stdint.h>

#define PS         "ps"  /**< Command name for the ps process */

static char * ps_args[] = {PS, 0};  /**< Arguments for the ps process */

/**
 * @brief Executes the ps process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t psProcess(int argc, char** argv);

#endif