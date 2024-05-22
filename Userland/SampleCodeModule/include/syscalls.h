#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>

int writeScreen(uint64_t fd, char* buffer, uint64_t len);
int readScreen(uint64_t fd, char* buffer, uint64_t len);

#endif