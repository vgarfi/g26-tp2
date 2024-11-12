/**
 * @file testSync.h
 * @brief Definition of synchronization test function and related constants.
 */

#ifndef __TEST_SYNC_H__
#define __TEST_SYNC_H__

#include <stdint.h>

#define TEST_SYNC   "synchro"  /**< Command name for the synchronization test */

/**
 * @brief Initializes the synchronization testing.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the test.
 */
uint64_t initializeSyncTesting(uint64_t argc, char *argv[]);

#endif