#include "syscall.h"
#include "test_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoryManagerADT.h"
#include "test_mm.h"

#define MAX_BLOCKS 128

typedef struct MM_rq {
  void *address;
  uint32_t size;
} mm_rq;

uint64_t test_mm(uint64_t argc, char *argv[]) {
    mm_rq mm_rqs[MAX_BLOCKS];
    uint8_t rq;
    uint32_t total;
    uint64_t max_memory;

    if (argc != 2)
        return -1;

    if ((max_memory = satoi(argv[1])) <= 0){
        return -1;
    }
        
    size_t total_memory = 1024 * 1024; // 1 MB
    size_t block_size = 64; // Bloques de 64 bytes
    void *memory = malloc(total_memory);
    if (memory == NULL) {
        printf("Error: No se pudo asignar memoria para el memory manager\n");
        return -1;
    }

    MemoryManagerADT memory_manager = initialize_mm(memory, total_memory, block_size);
    if (memory_manager == NULL) {
        printf("Error: No se pudo inicializar el memory manager\n");
        free(memory);
        return -1;
    }

    printf("Inicializando con %zu bytes de memoria (máximo solicitado: %lu bytes)\n", total_memory, max_memory);

    while (1) {
        rq = 0;
        total = 0;
        // Request as many blocks as we can
        while (rq < MAX_BLOCKS && total < max_memory) {
            mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
            mm_rqs[rq].address = malloc_mm(memory_manager, mm_rqs[rq].size);

            if (mm_rqs[rq].address) {
                total += mm_rqs[rq].size;
                printf("Bloque %d reservado: %u bytes en la dirección %p (total reservado: %u bytes)\n", rq, mm_rqs[rq].size, mm_rqs[rq].address, total);
                rq++;
            } else {
              if(rq==1)
                printf("Error al reservar bloque %d: %u bytes\n", rq, mm_rqs[rq].size);
            }
        }

        // Set
        uint32_t i;
        for (i = 0; i < rq; i++) {
            if (mm_rqs[i].address) {
                memset(mm_rqs[i].address, i, mm_rqs[i].size);
                printf("Bloque %d inicializado con valor %d\n", i, i);
            }
        }

        // Check
        for (i = 0; i < rq; i++) {
            if (mm_rqs[i].address) {
                if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size)) {
                    printf("test_mm ERROR: Fallo al comprobar el bloque %d en la dirección %p\n", i, mm_rqs[i].address);
                    return -1;
                } else {
                    printf("Bloque %d verificado correctamente\n", i);
                }
            }
        }

        // Free
        for (i = 0; i < rq; i++) {
            if (mm_rqs[i].address) {
                free_mm(memory_manager, mm_rqs[i].address);
                printf("Bloque %d liberado de la dirección %p\n", i, mm_rqs[i].address);
            }
        }

        printf("Ciclo de reserva, verificación y liberación completado.\n");
    }

    free(memory); // Liberar la memoria utilizada por el memory manager
    printf("Memoria del memory manager liberada.\n");
    return 0;
}

int main(int argc, char *argv[]) {
    return test_mm(argc, argv);
}