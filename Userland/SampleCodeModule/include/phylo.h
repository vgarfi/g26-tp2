/**
 * @file phylo.h
 * @brief Definition of the phylos process function and related constants.
 */

#include <stdint.h>

#ifndef __PHYLO_H__
#define __PHYLO_H__

#define PHYLOS "phylos"  /**< Command name for the phylos process */

/**
 * @brief Executes the phylos process.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the process.
 */
int64_t phylos(int argc, char *argv[]);

#endif