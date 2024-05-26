#ifndef __SPEAKER_H_
#define __SPEAKER_H_

#include <stdint.h>

void beep(uint64_t secs);

void outb(int memPos, int output);
int inb(int memPos);

#endif