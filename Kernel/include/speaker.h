#ifndef __SPEAKER_H_
#define __SPEAKER_H_

#define DOFREQ 261
#define DOSOSTFREQ 277
#define DOMENFREQ 523
#define REFREQ 293
#define MIFREQ 329
#define FAFREQ 349
#define FASOSTFREQ 369
#define SOLFREQ 392
#define SOLSOSTFREQ 415
#define LAFREQ 440
#define SIFREQ 493

#include <stdint.h>

void beep(uint64_t secs, uint64_t freq);

void outb(int memPos, int output);
int inb(int memPos);

void playEasterEggSong();

#endif