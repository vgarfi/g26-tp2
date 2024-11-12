// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <stdio.h>
#include <syscalls.h>
#include <testSync.h>
#include <testUtil.h>
#include <string.h>

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

int64_t myProcessInc(int argc, char *argv[]) {
  uint64_t n;
  int8_t inc;
  int8_t useSem;

  if (argc < 3)
    return -1;

  if ((n = satoi(argv[1])) <= 0)
    return -1;
  if ((inc = satoi(argv[2])) == 0)
    return -1;
  if ((useSem = satoi(argv[3])) < 0)
    return -1;

  if (useSem)
    if (sysCreateSem(SEM_ID, 1) == -1) {
      printf("testSync: ERROR creating semaphore\n", 0,0,0);
      return -1;
    }
 
  uint64_t i;
  for (i = 0; i < n; i++) {
    if (useSem)
      sysWaitSem(SEM_ID);
    slowInc(&global, inc);
    if (useSem)
      sysPostSem(SEM_ID);
  }

  return 0;
}

uint64_t testSync(uint64_t argc, char *argv[]) { //{n, useSem, 0}
  uint64_t pids[2 * TOTAL_PAIR_PROCESSES];
  printf("testSync: CREATED\n", 0,0,0);
  int testScope = sysGetScope(sysGetCurrentPid());
  if (argc <= 2)
    return 1;

  char *argvDec[] = {"myProcessInc", argv[1], "-1", argv[2], 0};
  char *argvInc[] = {"myProcessInc", argv[1], "1", argv[2], 0};

  global = 0;

  uint64_t i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    pids[i] = sysCreateProcess("myProcessInc", 4, argvDec, myProcessInc, testScope);
    pids[i + TOTAL_PAIR_PROCESSES] = sysCreateProcess("myProcessInc", 4, argvInc, myProcessInc, testScope);

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
  printf("Final value: %d\n", global, 0,0);
  return 0;
}

static char * syncArgsMemorySem[] = {TEST_SYNC, "5", "1", 0};
static char * syncArgsMemoryNotSem[] = {TEST_SYNC, "5", "0", 0};

uint64_t initializeSyncTesting(uint64_t argc, char *argv[]) {
  printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
    char option[5];
    int read = scanf(option, 5);
    while (read != -1 && strcasecmp(option, "y") != 0 && strcasecmp(option, "n") != 0) {
        printColor("ERROR: ",0x00FF0000);
        printf(option,0,0,0);
        printf(" is not a valid option",0,0,0);
        printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
        read = scanf(option, 5);
    }

    if (read == -1) {
      return 0;
    }
    
    printf("\nYou decided ",0,0,0);
    if (strcasecmp(option, "n") == 0) printf("not ",0,0,0);
    printf("to use semaphores. Starting tests...\n",0,0,0);

    int testPid;
    int testScope = sysGetScope(sysGetCurrentPid());

    if (strcasecmp(option, "n") == 0) {
        testPid = sysCreateProcess(TEST_SYNC, 3, syncArgsMemoryNotSem,  (int64_t (*)(int, char**))testSync, testScope);
    } else {
        testPid = sysCreateProcess(TEST_SYNC, 3, syncArgsMemorySem,  (int64_t (*)(int, char**))testSync, testScope);
    }
    sysNice(testPid, 5);
    sysWaitPid(testPid);
    return 0;
}