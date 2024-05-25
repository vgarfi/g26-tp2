#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>

int writeScreen(uint64_t fd, char* buffer, uint64_t len, uint64_t hexColor);
int readScreen(uint64_t fd, char* buffer, uint64_t len);
void sleep(uint64_t secs, uint64_t ms);
int clearScreen();
uint8_t upArrowValue();
uint8_t leftArrowValue();
uint8_t downArrowValue();
uint8_t rightArrowValue();
int printRectangle(uint32_t hexColor);
int printSquare(uint64_t side, uint32_t hexColor);
int setCursorPosition(uint64_t x, uint64_t y);
int beepSound(uint64_t secs);
char* getTime(void);
char* getDate(void);
int zoomIn(void);
int zoomOut(void);

#endif