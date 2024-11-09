#ifndef TEST_PROC_H
#define TEST_PROC_H

#include <stdint.h>

#define TEST_PROCESSES        "process"
#define TEST_PRIORITY        "priority"
#define TEST_MEMORY           "memory"

#define MINOR_WAIT 1000000 // TODO: Change this value to prevent a process from flooding the screen
#define WAIT 10000000      // TODO: Change this value to make the wait long enough to see theese processes beeing run at least twice

#define TOTAL_PROCESSES 5
#define LOWEST 1  // TODO: Change as required
#define MEDIUM 2  // TODO: Change as required
#define HIGHEST 3 // TODO: Change as required

enum State {
  RUNNING,
  BLOCKED,
  KILLED
};

typedef struct P_rq {
  int pid;
  enum State state;
} p_rq;


void testPriorities(void);
int64_t testProcesses(uint64_t argc, char *argv[]);

#endif