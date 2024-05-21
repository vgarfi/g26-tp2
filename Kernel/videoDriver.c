#include <videoDriver.h>
#include <defs.h>
#include <fonts.h>
#include <globals.h>
#include <lib.h>

static char buffer[64] = { '0' };


struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated 
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;


Cursor cursor = {0, 0}; 

void putPixel(uint8_t* framebuffer,uint64_t offset,uint32_t hexColor){
	framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> BYTE_LENGHT) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> TWO_BYTE_LENGHT) & 0xFF;
}
void putPixelAt(uint32_t hexColor, int x, int y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    putPixel(framebuffer,offset,hexColor);
}

void printLine(uint8_t* framebuffer,uint64_t offset,uint32_t fgColor,uint32_t bgColor ,uint8_t mask,int limit,int step){
	uint64_t off = offset;
	uint32_t hexColor;
	for(int i=0; i < limit; i++,off+=step){
		if (mask & (1 << (BYTE_LENGHT - 1 - i))) {
			hexColor = fgColor;
		} 
		else{
			hexColor = bgColor;
		}
		putPixel(framebuffer,off,hexColor);
	}
}

void printLineAt(int x,int y,uint32_t fgColor,uint32_t bgColor, uint8_t mask,int limit,int step){
	uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
	uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
	printLine(framebuffer,offset,fgColor,bgColor,mask,limit,step);
}

void printRectAt(int x1,int y1,int x2,int y2,uint32_t hexColor){
	int limit = x2 - x1;
	uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
	uint64_t offset = (x1 * ((VBE_mode_info->bpp)/8)) + (y1 * VBE_mode_info->pitch);
	for(;y1<y2;y1++,offset+=VBE_mode_info->pitch){
		printLine(framebuffer,offset,hexColor,hexColor,255,limit,((VBE_mode_info->bpp)/8));
	}
}


void print_char(unsigned char c) {
	FontBitmap fontBitMap = getCurrentFont(&global_font_manager);
	unsigned char* bitmap = fontBitMap.bitmap;
	int width = fontBitMap.size.width;
	int height = fontBitMap.size.height;

	uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
	if(cursor.posX == (VBE_mode_info->width)*((VBE_mode_info->bpp)/8)){
			cursor.posX = 0;
			cursor.posY += height * VBE_mode_info->pitch;
	}
	uint64_t offset = cursor.posX + cursor.posY;

	if (width == BYTE_LENGHT) {
		
		for (int y_pos = 0; y_pos < height; y_pos++,offset+=VBE_mode_info->pitch) {
			printLine(framebuffer,offset,0x00ffffff,0x00000000,bitmap[y_pos + (c-31) * height],BYTE_LENGHT,((VBE_mode_info->bpp)/8));
			//print_char_row(x, y + y_pos, bitmap[y_pos + (c-31) * height]);
		}
	}
	else {
		for (int y_pos = 0, pY = 0; y_pos < height*2; y_pos+=2, pY++,offset+=VBE_mode_info->pitch) {
			printLine(framebuffer,offset,0x00FFFFFF,0x00000000,bitmap[y_pos + (c-31) * height*2],BYTE_LENGHT,((VBE_mode_info->bpp)/8));
			printLine(framebuffer,offset+(width*((VBE_mode_info->bpp)/8)/2),0x00ffffff,0x00000000,bitmap[y_pos + (c-31) * height*2 + 1],BYTE_LENGHT,((VBE_mode_info->bpp)/8));
			//print_char_row_2_byte(x, y + pY, data1, data2);
		}
	}

	cursor.posX += ((VBE_mode_info->bpp)/8)*width;
}

void print(char *characters){
	int widthChar = getCurrentFont(&global_font_manager).size.width;
	for(int i=0,offset = 0;characters[i] != 0;i++,offset+=widthChar){
		print_char(characters[i]);
	}
}
/*
void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    print(buffer,20,20);
}


*/
void clearScreen(){
	memset(VBE_mode_info->framebuffer,0,3*VBE_mode_info->height * VBE_mode_info->width);
}

void scrol(int lines){
	int offset = lines * getCurrentFont(&global_font_manager).size.height * VBE_mode_info->width * 3;
	memcpy(VBE_mode_info->framebuffer,(VBE_mode_info->framebuffer + offset),3* VBE_mode_info->width * (VBE_mode_info->height -lines * getCurrentFont(&global_font_manager).size.height));
	memset(VBE_mode_info->framebuffer + 3*VBE_mode_info->height * VBE_mode_info->width - 3* VBE_mode_info->width * lines * getCurrentFont(&global_font_manager).size.height,0,3* VBE_mode_info->width * lines * getCurrentFont(&global_font_manager).size.height);
}

