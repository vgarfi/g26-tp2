#include <stdint.h>

uint32_t GetUint();
uint32_t GetUniform(uint32_t max);
uint8_t memcheck(void *start, uint8_t value, uint32_t size);
int64_t satoi(char *str);
void bussyWait(uint64_t n);
void endlessLoop();
void endlessLoopPrint(uint64_t wait);