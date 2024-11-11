/**
 * @file testProc.h
 * @brief Definition of process test functions and related constants.
 */

#ifndef TEST_PROC_H
#define TEST_PROC_H

#include <stdint.h>

#define TEST_PROCESSES        "process"  /**< Command name for the process test */
#define TEST_PRIORITY         "priority" /**< Command name for the priority test */
#define TEST_MEMORY           "memory"   /**< Command name for the memory test */

#define MINOR_WAIT 1000000 /**< Minor wait time to prevent a process from flooding the screen */
#define WAIT 10000000      /**< Wait time to make the wait long enough to see these processes being run at least twice */

#define TOTAL_PROCESSES 5
#define LOWEST 3  /**< Lowest priority */
#define MEDIUM 6  /**< Medium priority */
#define HIGHEST 10 /**< Highest priority */

/**
 * @enum State
 * @brief Enumeration of process states.
 */
enum State {
  RUNNING,
  BLOCKED,
  KILLED
};

/**
 * @struct P_rq
 * @brief Structure representing a process request.
 */
typedef struct P_rq {
  int pid;           /**< Process ID */
  enum State state;  /**< State of the process */
} p_rq;

/**
 * @brief Tests process priorities.
 */
void testPriorities(void);

/**
 * @brief Executes the process test.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return Status code of the test.
 */
int64_t testProcesses(uint64_t argc, char *argv[]);

#endif