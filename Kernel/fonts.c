#include <defs.h>
#include <fonts.h>
#include <bitmaps.h>

unsigned const char* fonts[] = {fontBitMap_8x12,fontBitMap_8x14,fontBitMap_16x18,fontBitMap_16x22,fontBitMap_16x24,fontBitMap_16x28, fontBitMap_16x32};

Size sizes[7] = {{6,8,12},{8,8,14},{10,16,18},{11,16,22},{12,16,24},{14,16,28}, {16,16,32}};

static FontManager global_font_manager;

// Function to initialize FontManager
void init_font_manager() {
    for (int i = 0; i < FONTS_QUANTITY; i++) {
        global_font_manager.fonts[i].bitmap = fonts[i];
        global_font_manager.fonts[i].size.width = sizes[i].width;
        global_font_manager.fonts[i].size.height = sizes[i].height;
        global_font_manager.fonts[i].size.real_width = sizes[i].real_width;
    }
	
    global_font_manager.current_font_index = DEFAULT_FONT;
}

// Funtion to select a font
int set_current_font(int index) {
    if (index >= 0 && index < FONTS_QUANTITY) {
        global_font_manager.current_font_index = index;
        return 0;
    }
    return 1; 
}

// Function to get the current font
FontBitmap get_current_font() {
    return global_font_manager.fonts[global_font_manager.current_font_index];
}

int size_up(){
    return set_current_font(global_font_manager.current_font_index+1);
}

int size_down(){
    return set_current_font(global_font_manager.current_font_index-1);
}

int get_zoom(){
    return global_font_manager.current_font_index;
}

int set_zoom(int zoom_level){
    return set_current_font(zoom_level);
}