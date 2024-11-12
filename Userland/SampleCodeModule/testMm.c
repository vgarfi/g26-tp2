// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
  mm_rq mmRqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;
  uint64_t maxMemory;

  if (argc != 2){
    return -1;
  }

  if ((maxMemory = satoi(argv[1])) <= 0){
    return -1;
  }

  while (1) {
    rq = 0;
    total = 0;

    while (rq < MAX_BLOCKS && total < maxMemory) {
      mmRqs[rq].size = GetUniform(maxMemory - total - 1) + 1;
      mmRqs[rq].address = sysMalloc(mmRqs[rq].size);

      if (mmRqs[rq].address) {
        total += mmRqs[rq].size;
        rq++;
      }
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
    {
      if (mmRqs[i].address)
      {
        memset(mmRqs[i].address, i, mmRqs[i].size);
      }
    }

    // Check
    for (i = 0; i < rq; i++){
      if (mmRqs[i].address){
        if (!memcheck(mmRqs[i].address, i, mmRqs[i].size)) {
          printf("testMm ERROR\n", 0, 0, 0);
          return -1;
        }
      }
    }

    // Free
    for (uint32_t i = 0; i < rq; i++){
      if (mmRqs[i].address){
        sysFree(mmRqs[i].address);
      }
    }
  }
}