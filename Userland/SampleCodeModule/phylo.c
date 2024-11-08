#include <phylo.h>

#include <stdint.h>
#include <stdio.h>
#include "include/syscalls.h"
#include "include/test_sync.h"
#include <test_util.h>
#include <string.h>

#define NUM_FILOSOFOS 10

char tenedores[NUM_FILOSOFOS][20];   // Semáforos para los tenedores
int* estado;        // Estados de los filósofos

// Estados posibles para los filósofos
#define PENSANDO 0
#define COMIENDO 1

uint64_t filosofo(uint64_t argc, char *argv[]) {
    char id = atoi(argv[1]);

    int tenedor_izq = id;                        // Tenedor a la izquierda
    int tenedor_der = (id + 1) % NUM_FILOSOFOS;  // Tenedor a la derecha

    while (1) {
        // Filósofo pensando
        estado[id] = PENSANDO;
        //sysSleep(3, 0); // Pensar
        for(int i = 0; i < 9999999; i++);

        if (id % 2 == 0) {  // Filósofo par
            sysWaitSem(tenedores[tenedor_der]);
            sysWaitSem(tenedores[tenedor_izq]);
        } else {  // Filósofo impar
            sysWaitSem(tenedores[tenedor_izq]);
            sysWaitSem(tenedores[tenedor_der]);
        }

        // Filósofo comiendo
        estado[id] = COMIENDO;

        for(int i = 0; i < NUM_FILOSOFOS; i++) {
            if(estado[i] == 0){
                printf(" . ", 0, 0, 0);
            }
            else {
                printf(" E ", 0, 0, 0);
            }
        }
        printf("\n", 0, 0, 0);

        //printf("Filosofo %d ha comenzado a comer.\n", id, 0, 0);
        //sysSleep(1, 0); // Comer
        for(int i = 0; i < 9999999; i++);

        // Filósofo termina de comer
        //printf("Filosofo %d ha terminado de comer.\n", id, 0, 0);
        // Soltar los tenedores
        sysPostSem(tenedores[tenedor_izq]);
        sysPostSem(tenedores[tenedor_der]);
        
        estado[id] = PENSANDO;
        //sysSleep(3, 0);
    }
}

void generar_nombre_tenedor(char *buffer, int id) {
    char nombre_base[] = "tenedor_";
    strcpy(buffer, nombre_base);
    int len = strlen(buffer);
    buffer[len] = '0' + id;
    buffer[len + 1] = '\0';
}

uint64_t phylos(uint64_t argc, char *argv[]) {
    int phylos_scope = sysGetScope(sysGetCurrentPid());
    int pids[NUM_FILOSOFOS];

    // Inicializar semáforos (tenedores)
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        generar_nombre_tenedor(tenedores[i], i);
        sysCreateSem(tenedores[i], 1);
        estado[i] = PENSANDO; // Inicialmente, todos están pensando
    }

    // Crear procesos para cada filósofo
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        char id_string[NUM_FILOSOFOS][3];
        itoa(i, id_string, 10);
        char *argv[] = {"filosofo", id_string, 0};

        int pid = sysCreateProcess("filosofo", 2, argv, filosofo, phylos_scope);
        pids[i] = pid;
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sysWaitPid(pids[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        sysCloseSem(tenedores[i]);
    }
    return 0;
}