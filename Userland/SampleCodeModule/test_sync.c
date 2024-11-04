#include <stdint.h>
#include <stdio.h>
#include "include/syscalls.h"
#include "include/test_sync.h"
#include <test_util.h>

#define SEM_ID "sem"
#define TOTAL_PAIR_PROCESSES 2

int64_t global; // shared memory

void slowInc(int64_t *p, int64_t inc) {
  uint64_t aux = *p;
  sysYield(); // This makes the race condition highly probable
  aux += inc;
  *p = aux;
  printf(".",0,0,0);
}

uint64_t my_process_inc(uint64_t argc, char *argv[]) {
  uint64_t n;
  int8_t inc;
  int8_t use_sem;

  if (argc < 3)
    return -1;

  if ((n = satoi(argv[1])) <= 0)
    return -1;
  if ((inc = satoi(argv[2])) == 0)
    return -1;
  if ((use_sem = satoi(argv[3])) < 0)
    return -1;

  if (use_sem)
    if (sysCreateSem(SEM_ID, 1) == -1) {
      printf("test_sync: ERROR creating semaphore\n", 0,0,0);
      return -1;
    }
 
  uint64_t i;
  for (i = 0; i < n; i++) {
    if (use_sem)
      sysWaitSem(SEM_ID);
    slowInc(&global, inc);
    if (use_sem)
      sysPostSem(SEM_ID);
  }

  return 0;
}

uint64_t test_sync(uint64_t argc, char *argv[]) { //{n, use_sem, 0}
  uint64_t pids[2 * TOTAL_PAIR_PROCESSES];
  printf("test_sync: CREATED\n", 0,0,0);
  
  if (argc <= 2)
    return 1;

  char *argvDec[] = {"my_process_inc", argv[1], "-1", argv[2], 0};
  char *argvInc[] = {"my_process_inc", argv[1], "1", argv[2], 0};

  global = 0;

  uint64_t i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    pids[i] = sysCreateProcess("my_process_inc", 4, argvDec, my_process_inc);
    pids[i + TOTAL_PAIR_PROCESSES] = sysCreateProcess("my_process_inc", 4, argvInc, my_process_inc);

    sysNice(pids[i], 10);
    sysNice(pids[i + TOTAL_PAIR_PROCESSES], 10);
  }
  printf("Processes INCs CREATED\n", 0,0,0);
  printf("Slowing incrementating", 0,0,0);

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    sysWaitPid(pids[i]);
    sysWaitPid(pids[i + TOTAL_PAIR_PROCESSES]);
  }

  sysCloseSem(SEM_ID);

  printf("\nProcesses WAITED\n", 0,0,0);
  printf("Final value: %d", global, 0,0);
  printColor("\n$", 0x0000FF00);
  print("> ");
  sysShowCursor();

  return 0;
}

static char * sync_args_memory_sem[] = {TEST_SYNC, "5", "1", 0};
static char * sync_args_memory_not_sem[] = {TEST_SYNC, "5", "0", 0};

uint64_t initialize_sync_testing(uint64_t argc, char *argv[]) {
  printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
    char option[5];
    scanf(option, 5);
    while (strcasecmp(option, "y") != 0 && strcasecmp(option, "n") != 0) {
        printColor("ERROR: ",0x00FF0000);
        printf(option,0,0,0);
        printf(" is not a valid option",0,0,0);
        printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
        scanf(option, 5);
    }
    
    printf("\nYou decided ",0,0,0);
    if (strcasecmp(option, "n") == 0) printf("not ",0,0,0);
    printf("to use semaphores. Starting tests...\n",0,0,0);

    int testPid;

    if (strcasecmp(option, "n") == 0) {
        testPid = sysCreateProcess(TEST_SYNC, 3, sync_args_memory_not_sem,  (int64_t (*)(int, char**))test_sync);
    } else {
        testPid = sysCreateProcess(TEST_SYNC, 3, sync_args_memory_sem,  (int64_t (*)(int, char**))test_sync);
    }
    sysNice(testPid, 5);
}