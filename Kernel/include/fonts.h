/***************************************************
  fonts.h
****************************************************/

#include <bytes.h>

#ifndef FONT_H
#define FONT_H

#define FONTS_QUANTITY	3

#define S_FONT			0
#define M_FONT			1
#define B_FONT			2

#define DEFAULT_FONT	S_FONT

typedef struct {
	int width;
	int height;
} Size;

typedef struct {
    unsigned char *bitmap;
    Size size;
} FontBitmap;

typedef struct {
    FontBitmap fonts[FONTS_QUANTITY];
    int currentFontIndex;
} FontManager;

void initFontManager();
int setCurrentFont(int index);
FontBitmap getCurrentFont();
int sizeUp(void);
int sizeDown(void);

#endif