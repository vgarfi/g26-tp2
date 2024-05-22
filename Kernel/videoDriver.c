#include <videoDriver.h>
#include <defs.h>
#include <fonts.h>
#include <globals.h>
#include <lib.h>

static char buffer[64] = { '0' };
typedef struct vbe_mode_info_structure * VBEInfoPtr;
VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;
Cursor cursor = {0, 0};;
uint8_t * framebuffer;
uint16_t widthScreen;
uint16_t heightScreen;
uint16_t pitch;
uint8_t  bytesPerPixel;

void initializeVideoDriver(){
	framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
	widthScreen = 	VBE_mode_info->width;
	heightScreen = VBE_mode_info->height;
	pitch = VBE_mode_info->pitch;
	bytesPerPixel = VBE_mode_info->bpp/8;
}


void vdPrintRect(uint32_t hexColor){
	FontBitmap fontBitMap = getCurrentFont(&global_font_manager);
	unsigned char* bitmap = fontBitMap.bitmap;
	int width = fontBitMap.size.width;
	int height = fontBitMap.size.height;
	int offset = cursor.posX + cursor.posY;
	int y1 = cursor.posY / (VBE_mode_info->pitch*height);
	int y2 = height;
	for(;y1<y2;y1++,offset+=VBE_mode_info->pitch){
		vdPrintLine(offset,hexColor,hexColor,255,width,bytesPerPixel);
	}
}

void vdUpdateCursor(int x, int y){
	cursor.posX += x * bytesPerPixel * getCurrentFont(&global_font_manager).size.width;
	cursor.posY += y * pitch * getCurrentFont(&global_font_manager).size.height;
}

void vdPrintCursor(){
	if(cursor.posX == widthScreen* bytesPerPixel){
			cursor.posX = 0;
			cursor.posY += 12 * pitch;
	}
	vdPrintRect(0x00FFFFFF);
}

void vdSetCursor(int x, int y){

}

void vdPutPixel(uint64_t offset,uint32_t hexColor){
	framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> BYTE_LENGHT) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> TWO_BYTE_LENGHT) & 0xFF;
}

void vdPrintLine(uint64_t offset,uint32_t fgColor,uint32_t bgColor ,uint8_t mask,int limit,int step){
	uint64_t off = offset;
	uint32_t hexColor;
	for(int i=0; i < limit; i++,off+=step){
		if (mask & (1 << (BYTE_LENGHT - 1 - i))) {
			hexColor = fgColor;
		} 
		else{
			hexColor = bgColor;
		}
		vdPutPixel(off,hexColor);
	}
}

void vdPrintChar(unsigned char c) {
	FontBitmap fontBitMap = getCurrentFont(&global_font_manager);
	unsigned char* bitmap = fontBitMap.bitmap;
	int width = fontBitMap.size.width;
	int height = fontBitMap.size.height;

	if(cursor.posX == widthScreen* bytesPerPixel){
			cursor.posX = 0;
			cursor.posY += height * pitch;
	}
	uint64_t offset = cursor.posX + cursor.posY;

	if (width == BYTE_LENGHT) {
		
		for (int y_pos = 0; y_pos < height; y_pos++,offset+=pitch) {
			vdPrintLine(offset,0x00ffffff,0x00000000,bitmap[y_pos + (c-31) * height],BYTE_LENGHT,bytesPerPixel);
			//print_char_row(x, y + y_pos, bitmap[y_pos + (c-31) * height]);
		}
	}
	else {
		for (int y_pos = 0, pY = 0; y_pos < height*2; y_pos+=2, pY++,offset+=VBE_mode_info->pitch) {
			vdPrintLine(offset,0x00FFFFFF,0x00000000,bitmap[y_pos + (c-31) * height*2],BYTE_LENGHT,((VBE_mode_info->bpp)/8));
			vdPrintLine(offset+(width*bytesPerPixel/2),0x00ffffff,0x00000000,bitmap[y_pos + (c-31) * height*2 + 1],BYTE_LENGHT,bytesPerPixel);
			//print_char_row_2_byte(x, y + pY, data1, data2);
		}
	}
}

void vdPrint(char *characters){
	for(int i=0;characters[i] != 0;i++){
		vdPrintChar(characters[i]);
		vdUpdateCursor(1,0);
		vdPrintCursor();
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

void scroll(int lines) {
    int fontHeight = getCurrentFont(&global_font_manager).size.height;
    int offset = lines * fontHeight * VBE_mode_info->width * 3;
    int frameSize = 3 * VBE_mode_info->width * (VBE_mode_info->height - lines * fontHeight);
    int clearSize = 3 * VBE_mode_info->width * lines * fontHeight;

    memcpy(VBE_mode_info->framebuffer, VBE_mode_info->framebuffer + offset, frameSize);
    memset(VBE_mode_info->framebuffer + frameSize, 0, clearSize);
}
