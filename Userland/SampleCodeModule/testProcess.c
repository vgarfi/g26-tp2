#include <test_proc.h>
#include <test_util.h>
#include <syscalls.h>
#include <stdio.h>




uint8_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};

int64_t test_processes(uint64_t argc, char *argv[]) {
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t max_processes;
  char *argvAux[] = {0};

  printf("\nFui creado con %d argumentos: %d \n", argc, satoi(argv[1]), 0);

  if (argc != 2)
    return -1;

  /*if ((max_processes = satoi(argv[1])) <= 0)
    return -1;*/

  max_processes = 6;

  p_rq p_rqs[max_processes];
  printf("test_processes: Testing process administration...",0,0,0);
  while (1) {

    // Create max_processes processes
    for (rq = 0; rq < max_processes; rq++) {
      p_rqs[rq].pid = sysCreateProcess("endless_loop", 0, argvAux, endless_loop);

      if (p_rqs[rq].pid == -1) {
        printf("test_processes: ERROR creating process\n",0,0,0);
        return -1;
      } else {
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0) {
      for (rq = 0; rq < max_processes; rq++) {
        action = GetUniform(100) % 2;

        switch (action) {
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED) {
              if (sysKillProcess(p_rqs[rq].pid) == -1) {
                printf("test_processes: ERROR killing process\n",0,0,0);
                return -1;
              }
              p_rqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING) {
              if (sysBlockProcess(p_rqs[rq].pid) == -1) {
                printf("test_processes: ERROR blocking process\n",0,0,0);
                return -1;
              }
              p_rqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < max_processes; rq++)
        if (p_rqs[rq].state == BLOCKED && GetUniform(100) % 2) {
          if (sysUnblockProcess(p_rqs[rq].pid) == -1) {
            printf("test_processes: ERROR unblocking process\n",0,0,0);
            return -1;
          }
          p_rqs[rq].state = RUNNING;
        }
    }
  }
  printf("test_processes: Process tested succesfully",0,0,0);
}

void test_priorities(void) {
  uint8_t pids[TOTAL_PROCESSES];
  char *argv[] = {0};
  uint64_t i;

  printf("test_priorities: Testing Process Priorities...",0,0,0);


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
  
  printf("test_priorities: Process priorities tested succesfully",0,0,0);

}