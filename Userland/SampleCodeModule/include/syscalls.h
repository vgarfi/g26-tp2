#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>

int syswriteScreen(uint64_t fd, unsigned char* buffer, uint64_t len, uint64_t hexColor);
int sysreadScreen(uint64_t fd, unsigned char* buffer, uint64_t len);
void syssleep(uint64_t secs, uint64_t ms);
int sysclearScreen();
int sysclearKbEntry();

int sysctrlPressed();

uint8_t sysupArrowValue();
uint8_t sysleftArrowValue();
uint8_t sysdownArrowValue();
uint8_t sysrightArrowValue();
int sysprintRectangle(int x,int y,int base,int height,uint32_t hexColor);
int sysprintSquare(int x,int y , int side, uint32_t hexColor);
int syssetCursorPosition(uint64_t x, uint64_t y);
int sysbeepSound(uint64_t secs, uint64_t freq);

int sysgetSecs(void);
int sysgetMins(void);
int sysgetHour(void);

int sysgetDay(void);
int sysgetMonth(void);
int sysgetYear(void);

int syszoomIn(void);
int syszoomOut(void);
int sysgetZoomLevel(void);
int syssetZoomLevel(int zoomLevel);

int sysprintRegs(void);
int sysprintCursor();
int syshideCursor();
int sysshowCursor();

#endif