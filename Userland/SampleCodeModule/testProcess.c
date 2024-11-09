#include <testProc.h>
#include <testUtil.h>
#include <syscalls.h>
#include <stdio.h>

uint8_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};
void finish_testing();

int64_t testProcesses(uint64_t argc, char *argv[]) {
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t max_processes;
  char *argvAux[] = {0};
  TScope test_scope = sysGetScope(sysGetCurrentPid());
  
  if (argc != 2)
    return -1;

  if ((max_processes = satoi(argv[1])) <= 0)
    return -1;

  p_rq p_rqs[max_processes];
  printf("testProcesses: Testing process administration...",0,0,0);
  while (1) {
    for (rq = 0; rq < max_processes; rq++) {
      p_rqs[rq].pid = sysCreateProcess("endlessLoop", 0, argvAux, (int64_t (*)(int, char**))endlessLoop, test_scope);
      if (p_rqs[rq].pid == -1) {
        printf("testProcesses: ERROR creating process\n",0,0,0);
        return -1;
      } else {
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    printf("\nCREATED %d PROCESSES", max_processes, 0, 0);


    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0) {
      for (rq = 0; rq < max_processes; rq++) {
        action = GetUniform(100) % 2;
        switch (action) {
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED) {
              if (sysKillProcess(p_rqs[rq].pid) == -1) {
                printf("testProcesses: ERROR killing process\n",0,0,0);
                return -1;
              }
              p_rqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING) {
              if (sysBlockProcess(p_rqs[rq].pid) == -1) {
                printf("testProcesses: ERROR blocking process\n",0,0,0);
                return -1;
              }
              p_rqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < max_processes; rq++){
        if (p_rqs[rq].state == BLOCKED && GetUniform(100) % 2) {
          if (sysUnblockProcess(p_rqs[rq].pid) == -1) {
            printf("testProcesses: ERROR unblocking process\n",0,0,0);
            return -1;
          }
          p_rqs[rq].state = RUNNING;
        }
        printf("\nALIVE: %d, DEAD: %d", alive, max_processes-alive, 0);
      }
    }
    printf("\nKILLED %d PROCESSES", max_processes, 0, 0);
  }
}

void testPriorities(void) {
  uint8_t pids[TOTAL_PROCESSES];
  char *argv[] = {0};
  uint64_t i;
  TScope test_scope = sysGetScope(sysGetCurrentPid());
  int fds[] = {0,1}; 
  
  printf("testPriorities: Testing Process Priorities...",0,0,0);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = sysCreateProcess("endlessLoopPrint", 0, argv, (int64_t (*)(int, char**))endlessLoopPrint, test_scope);

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
  finish_testing();
  return;
}

void finish_testing() {
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
    printf(".", 0,0,0);
    printColor("\n$", 0x0000FF00);
    print("> ");
    sysShowCursor();
    // sysKillProcess(sysGetCurrentPid());
}