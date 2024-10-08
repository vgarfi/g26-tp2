#ifndef __SYSCALLHANDLE_H_
#define __SYSCALLHANDLE_H_

#include <stdint.h>

int setCursor(uint64_t x, uint64_t y);
int hideCursor();
int showCursor();
int printCursor();

int upArrowValue();
int leftArrowValue();
int downArrowValue();
int rightArrowValue();

int printRect(int x,int y,int base,int height,uint32_t hexColor);
int printSquare (int x, int y,int side, uint32_t hexColor);

int clearScreen();
int msSleep(uint64_t secs, uint64_t ticks);     // rdi : ms
int printRegs(void);

int sound(uint64_t ms, uint64_t freq);

int getCurrentSeconds(void);
int getCurrentMinutes(void);
int getCurrentHours(void);

int getCurrentDay(void);
int getCurrentMonth(void);
int getCurrentYear(void);

int incSize();
int decSize();
int getZoomLevel();
int setZoomLevel(int zoomLevel);

int read(uint64_t fd, char * buf, uint64_t count);
int write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor);

uint8_t getPid();
int exit();

int cleanKbBuffer(void);

int isctrlPressed(void);

#endif