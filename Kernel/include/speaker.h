#ifndef __SPEAKER_H_
#define __SPEAKER_H_

#include <stdint.h>

void beep(uint64_t ms, uint64_t freq);
void nosound();
void outb(int memPos, int output);
int inb(int memPos);
void playSound(uint32_t nFrequence);
#endif