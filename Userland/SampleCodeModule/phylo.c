// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <phylo.h>

#include <stdint.h>
#include <stdio.h>
#include "include/syscalls.h"
#include "include/testSync.h"
#include <testUtil.h>
#include <string.h>

#define PHYLOS_QTY  5
#define MAX_LEN     20

char forks[PHYLOS_QTY][MAX_LEN];
int* states;        

// Posisble philosophers states
#define THINKING 0
#define EATING 1

int64_t philosopher(int argc, char *argv[]) {
    int id = atoi(argv[1]);

    int leftFork = id;
    int rightFork = (id + 1) % PHYLOS_QTY;

    while (1) {
        // Philosopher just thinking
        states[id] = THINKING;
        sysSleep(0, 1);

        if (id % 2 == 0) {  // Even phylo
            sysWaitSem(forks[rightFork]);
            sysWaitSem(forks[leftFork]);
        } else {  // Odd phylo
            sysWaitSem(forks[leftFork]);
            sysWaitSem(forks[rightFork]);
        }

        // Pilosopher just eating
        states[id] = EATING;

        for(int i = 0; i < PHYLOS_QTY; i++) {
            if(states[i] == 0){
                printf(" . ", 0, 0, 0);
            }
            else {
                printf(" E ", 0, 0, 0);
            }
        }
        printf("\n", 0, 0, 0);

        sysSleep(0, 1); // Eating time!

        // Finished eating. Just leaving the forks
        sysPostSem(forks[leftFork]);
        sysPostSem(forks[rightFork]);
        
        states[id] = THINKING;
        sysSleep(0, 1);
    }
}

void generateForkName(char *buffer, int id) {
    char baseName[] = "fork_";
    int timestamp = sysGetSecs();
    char timestampBuffer[10], idBuffer[5];
    itoa(id, idBuffer, 10);
    itoa(timestamp, timestampBuffer, 10);
    strconcat(buffer, baseName, idBuffer);
    strconcat(buffer, buffer, timestampBuffer);
}

int64_t phylos(int argc, char *argv[]) {
    int phylosScope = sysGetScope(sysGetCurrentPid());

    // Initialize semaphores (forks)
    for (int i = 0; i < PHYLOS_QTY; i++) {
        generateForkName(forks[i], i);
        sysCreateSem(forks[i], 1);
        states[i] = THINKING; // Initially, they are all thinking
    }

    for (int i = 0; i < PHYLOS_QTY; i++) {
        char id_string[3];
        itoa(i, id_string, 10);
        char *argv[] = {"philosopher", id_string, 0};

        sysCreateProcess("philosopher", 2, argv, philosopher, phylosScope);
    }

    sysBlockProcess(sysGetCurrentPid()); // Phylo process has nothing else to do
    return 0;
}