#include <defs.h>
#include <fonts.h>


unsigned const char* fonts[] = {fontBitMap_8x12, fontBitMap_8x16, fontBitMap_16x32};
const Size size_16x32 = {16,32};
const Size size_8x16 = {8,16};
const Size size_8x12 = {8,12};

Size sizes[3] = {{8,12}, {8,16}, {16,32}};

const FontBitmap fb1 = {fontBitMap_16x32, {16,32}};
const FontBitmap fb2 = {fontBitMap_8x16, {8,16}};
const FontBitmap fb3 = {fontBitMap_8x12, {8,12}};

static FontManager global_font_manager;

// Función para inicializar el FontManager
void initFontManager() {
    for (int i = 0; i < FONTS_QUANTITY; i++) {
        global_font_manager.fonts[i].bitmap = fonts[i];
        global_font_manager.fonts[i].size.width = sizes[i].width;
        global_font_manager.fonts[i].size.height = sizes[i].height;
    }
	
    global_font_manager.currentFontIndex = DEFAULT_FONT;
}

// Función para seleccionar un font
void setCurrentFont(int index) {
    if (index >= 0 && index < FONTS_QUANTITY) {
        global_font_manager.currentFontIndex = index;
    } 
}

// Función para obtener el font actual
FontBitmap getCurrentFont() {
    return global_font_manager.fonts[global_font_manager.currentFontIndex];
}