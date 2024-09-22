#include "syscall.h"
#include "test_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoryManagerADT.h"

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


    printf("Inicializando el manager con %zu bytes de memoria\n", total_memory);

    while (1) {
        rq = 0;
        total = 0;
        printf("Iniciando nueva iteración del ciclo principal\n");

        // Request as many blocks as we can
        while (rq < MAX_BLOCKS && total < max_memory)
        {
            mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
            //printf("Tamaño solicitado para el bloque: %d\n", mm_rqs[rq].size);

            mm_rqs[rq].address = malloc_mm(memory_manager, mm_rqs[rq].size);

            if (mm_rqs[rq].address == NULL) {
                //printf("Fallo al asignar bloque de tamaño %d\n", mm_rqs[rq].size);
            } else {
                printf("Bloque asignado de tamaño %d en dirección %p\n", mm_rqs[rq].size, mm_rqs[rq].address);
            }

            if (mm_rqs[rq].address)
            {
                total += mm_rqs[rq].size;
                rq++;
            }
        }

    // Set
    printf("Bloques asignados: %d\n", rq);
    uint32_t i;
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        memset(mm_rqs[i].address, i, mm_rqs[i].size);

    // Check
    for (i = 0; i < rq; i++){
      if (mm_rqs[i].address){
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size)) {
          printf("test_mm ERROR\n");
          return -1;
        }
      }
    }

    // Free
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        free_mm(memory_manager, mm_rqs[i].address);
  }

  free(memory); // Liberar la memoria utilizada por el memory manager
  return 0;
}

int main(int argc, char *argv[]) {
    return test_mm(argc, argv);
}
