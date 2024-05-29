#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>

int writeScreen(uint64_t fd, unsigned char* buffer, uint64_t len, uint64_t hexColor);
int readScreen(uint64_t fd, unsigned char* buffer, uint64_t len);
void sleep(uint64_t secs, uint64_t ms);
int clearScreen();
uint8_t upArrowValue();
uint8_t leftArrowValue();
uint8_t downArrowValue();
uint8_t rightArrowValue();
int printRectangle(int x,int y,int base,int height,uint32_t hexColor);
int printSquare(int x,int y , int side, uint32_t hexColor);
int setCursorPosition(uint64_t x, uint64_t y);
int beepSound(uint64_t secs);

int getSecs(void);
int getMins(void);
int getHour(void);

int getDay(void);
int getMonth(void);
int getYear(void);

int zoomIn(void);
int zoomOut(void);
int printRegs(void);
int printCursor();
int hideCursor();
int showCursor();

#endif