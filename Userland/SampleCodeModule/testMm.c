#include <syscalls.h>
#include <testUtil.h>
#include <testMm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 128

typedef struct MM_rq {
  void *address;
  uint32_t size;
} mm_rq;

void *memset(void *s, int c, size_t n) {
  unsigned char *ptr = s;
  unsigned char value = (unsigned char)c;

  for (size_t i = 0; i < n; i++) {
    ptr[i] = value;
  }

  return s;
}

uint64_t testMm(uint64_t argc, char *argv[]) {
  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;
  uint64_t max_memory;

  if (argc != 2){
    return -1;
  }

  if ((max_memory = satoi(argv[1])) <= 0){
    return -1;
  }

  while (1) {
    rq = 0;
    total = 0;

    while (rq < MAX_BLOCKS && total < max_memory) {
      mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
      mm_rqs[rq].address = sysMalloc(mm_rqs[rq].size);

      if (mm_rqs[rq].address) {
        total += mm_rqs[rq].size;
        rq++;
      }
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
    {
      if (mm_rqs[i].address)
      {
        memset(mm_rqs[i].address, i, mm_rqs[i].size);
      }
    }

    // Check
    for (i = 0; i < rq; i++){
      if (mm_rqs[i].address){
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size)) {
          printf("testMm ERROR\n", 0, 0, 0);
          return -1;
        }
      }
    }

    // Free
    for (uint32_t i = 0; i < rq; i++){
      if (mm_rqs[i].address){
        sysFree(mm_rqs[i].address);
      }
    }
  }
}