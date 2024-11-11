/**
 * @file ipc.h
 * @brief Definition of inter-process communication (IPC) functions and related constants.
 */

#ifndef __IPC_H__
#define __IPC_H__

#include <stdint.h>

#define CAT         "cat"       /**< Command name for the cat process */
#define WC          "wc"        /**< Command name for the word count process */
#define FILTER      "filter"    /**< Command name for the filter process */

/**
 * @brief Executes the cat process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t catProcess(int argc, char** argv);

/**
 * @brief Executes the word count process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t wcProcess(int argc, char** argv);

/**
 * @brief Executes the filter process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t filterProcess(int argc, char** argv);

#endif