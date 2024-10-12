#include <stdint.h>
#include <stdio.h>
#include <syscalls.h>
#include <testUtil.h>


#define MINOR_WAIT 1000000 // TODO: Change this value to prevent a process from flooding the screen
#define WAIT 10000000      // TODO: Change this value to make the wait long enough to see theese processes beeing run at least twice

#define TOTAL_PROCESSES 3
#define LOWEST 1  // TODO: Change as required
#define MEDIUM 2  // TODO: Change as required
#define HIGHEST 3 // TODO: Change as required

uint8_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};

void test_prio() {
  uint8_t pids[TOTAL_PROCESSES];
  char *argv[] = {0};
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = sysCreateProcess("endless_loop_print", 0, argv, endless_loop_print);

  bussy_wait(WAIT);
  printf("\nCHANGING PRIORITIES...\n", 0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysNice(pids[i], prio[i]);

  bussy_wait(WAIT);
  printf("\nBLOCKING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysBlockProcess(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysNice(pids[i], MEDIUM);

  printf("UNBLOCKING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysUnblockProcess(pids[i]);

  bussy_wait(WAIT);
  printf("\nKILLING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysKillProcess(pids[i]);
}