// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <testProc.h>
#include <testUtil.h>
#include <syscalls.h>
#include <stdio.h>

uint8_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};
void finishTesting();

int64_t testProcesses(uint64_t argc, char *argv[]) {
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t maxProcesses;
  char *argvAux[] = {0};
  TScope testScope = sysGetScope(sysGetCurrentPid());
  
  if (argc != 2)
    return -1;

  if ((maxProcesses = satoi(argv[1])) <= 0)
    return -1;

  p_rq pRqs[maxProcesses];
  printf("testProcesses: Testing process administration...",0,0,0);
  while (1) {
    for (rq = 0; rq < maxProcesses; rq++) {
      pRqs[rq].pid = sysCreateProcess("endlessLoop", 0, argvAux, (int64_t (*)(int, char**))endlessLoop, testScope);
      if (pRqs[rq].pid == -1) {
        printf("testProcesses: ERROR creating process\n",0,0,0);
        return -1;
      } else {
        pRqs[rq].state = RUNNING;
        alive++;
      }
    }

    printf("\nCREATED %d PROCESSES", maxProcesses, 0, 0);


    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0) {
      for (rq = 0; rq < maxProcesses; rq++) {
        action = GetUniform(100) % 2;
        switch (action) {
          case 0:
            if (pRqs[rq].state == RUNNING || pRqs[rq].state == BLOCKED) {
              if (sysKillProcess(pRqs[rq].pid) == -1) {
                printf("testProcesses: ERROR killing process\n",0,0,0);
                return -1;
              }
              pRqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (pRqs[rq].state == RUNNING) {
              if (sysBlockProcess(pRqs[rq].pid) == -1) {
                printf("testProcesses: ERROR blocking process\n",0,0,0);
                return -1;
              }
              pRqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < maxProcesses; rq++){
        if (pRqs[rq].state == BLOCKED && GetUniform(100) % 2) {
          if (sysUnblockProcess(pRqs[rq].pid) == -1) {
            printf("testProcesses: ERROR unblocking process\n",0,0,0);
            return -1;
          }
          pRqs[rq].state = RUNNING;
        }
        printf("\nALIVE: %d, DEAD: %d", alive, maxProcesses-alive, 0);
      }
    }
    printf("\nKILLED %d PROCESSES", maxProcesses, 0, 0);
  }
}

void testPriorities(void) {
  uint8_t pids[TOTAL_PROCESSES];
  char *argv[] = {0};
  uint64_t i;
  TScope testScope = sysGetScope(sysGetCurrentPid());
  
  printf("testPriorities: Testing Process Priorities...",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = sysCreateProcess("endlessLoopPrint", 0, argv, (int64_t (*)(int, char**))endlessLoopPrint, testScope);

  bussyWait(WAIT);
  printf("\nCHANGING PRIORITIES...\n", 0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysNice(pids[i], prio[i]);

  bussyWait(WAIT);
  printf("\nBLOCKING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysBlockProcess(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysNice(pids[i], MEDIUM);

  printf("UNBLOCKING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysUnblockProcess(pids[i]);

  bussyWait(WAIT);
  printf("\nKILLING...\n",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sysKillProcess(pids[i]);

  bussyWait(WAIT);
  sysPs();
  printf("\ntestPriorities: Process priorities tested succesfully\n",0,0,0);
  finishTesting();
  return;
}

void finishTesting() {
    bussyWait(WAIT*3);
    printf("\nFinishing testing in 3", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(" 2",0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(" 1",0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".", 0,0,0);
    bussyWait(WAIT);
    printf(".\n", 0,0,0);
}