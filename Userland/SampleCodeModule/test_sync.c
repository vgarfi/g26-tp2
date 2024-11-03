#include <stdint.h>
#include <stdio.h>
#include "include/syscalls.h"
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
  // TODO ver si por default hacemos que al crear un proceso, los FDs sean el de tu madre o si siempre es STDIN-STDPUT (pq en caso de testeos, que crean otros procesos, el wrapper de testeo tiene cambiado pero no los sub test que se crean)
  int fds[] =  {0,1}; 

  if (argc <= 2)
    return 1;

  char *argvDec[] = {"my_process_inc", argv[1], "-1", argv[2], 0};
  char *argvInc[] = {"my_process_inc", argv[1], "1", argv[2], 0};

  global = 0;

  uint64_t i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    pids[i] = sysCreateProcess("my_process_inc", 4, argvDec, my_process_inc, fds);
    pids[i + TOTAL_PAIR_PROCESSES] = sysCreateProcess("my_process_inc", 4, argvInc, my_process_inc, fds);

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