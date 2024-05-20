#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#
//void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void print_char(int x,int y, unsigned char c);
void putPixel(uint8_t* framebuffer,uint64_t offset,uint32_t hexcolor);
void putPixelAt(uint32_t hexColor, int x, int y);
void printLine(uint8_t* framebuffer,uint64_t offset,uint32_t fgColor,uint32_t bgColor,uint8_t mask,int limit,int step);
void printLineAt(int x,int y,uint32_t fgColor,uint32_t bgColor, uint8_t mask,int limit,int step);
void printRectAt(int x1,int y1,int x2,int y2,uint32_t hexColor);
void print(char *characters,int x, int y);
void clearScreen();
/*
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
*/
#endif
