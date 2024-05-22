#include <videoDriver.h>
#include <defs.h>
#include <fonts.h>
#include <globals.h>
#include <lib.h>

//static char buffer[64] = { '0' };
typedef struct vbe_mode_info_structure * VBEInfoPtr;
VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;
Cursor cursor = {0, 0};
uint8_t * framebuffer;
uint16_t widthScreen;
uint16_t heightScreen;
uint16_t pitch;
uint8_t  bytesPerPixel;
static uint32_t fgColor = 0x00FFFFFF;
static uint32_t bgColor = 0x00000000;
static int maxCharsInScreen = 8192; // chars per row * chars per column 
char charsInScreen[8192] = {' '};
static int index = 0;
void initializeVideoDriver(){
	framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
	widthScreen = 	VBE_mode_info->width;
	heightScreen = VBE_mode_info->height;
	pitch = VBE_mode_info->pitch;
	bytesPerPixel = VBE_mode_info->bpp/8;

}


void vdPrintRect(uint32_t hexColor){
	int y2 = getCurrentFont(&global_font_manager).size.height;
	int width = getCurrentFont(&global_font_manager).size.width;
	uint64_t offset = cursor.posX + cursor.posY;
	for(int y1=0;y1 < y2;y1++,offset+=pitch){
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
			cursor.posY += getCurrentFont(&global_font_manager).size.height * pitch;
	}
	vdPrintRect(0x00FFFFFF);
}

void vdSetCursor(int x, int y){
	cursor.posX = x * bytesPerPixel * getCurrentFont(&global_font_manager).size.width;
	cursor.posY = y * pitch * getCurrentFont(&global_font_manager).size.height;
}

void vdNewLine(){
	vdPrintRect(0x00000000);
	cursor.posX = 0;
	cursor.posY += pitch * getCurrentFont(&global_font_manager).size.height;
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
			vdPrintLine(offset,fgColor,bgColor,bitmap[y_pos + (c-31) * height],BYTE_LENGHT,bytesPerPixel);
		}
	}
	else {
		for (int y_pos = 0, pY = 0; y_pos < height*2; y_pos+=2, pY++,offset+=VBE_mode_info->pitch) {
			vdPrintLine(offset,fgColor,bgColor,bitmap[y_pos + (c-31) * height*2],BYTE_LENGHT,bytesPerPixel);
			vdPrintLine(offset+(width*bytesPerPixel/2),fgColor,bgColor,bitmap[y_pos + (c-31) * height*2 + 1],BYTE_LENGHT,bytesPerPixel);
		}
	}
}

void vdPrint(char *characters,uint32_t hexColor){
	fgColor = hexColor;
	for(int i=0;characters[i] != 0;i++){
		vdPrintChar(characters[i]);
		vdUpdateCursor(1,0);
		charsInScreen[index++] = characters[i];
		vdPrintCursor();
	}
}

void vdDeleteChar(){
	vdPrintChar(' ');
	if(cursor.posX == 0){
		vdUpdateCursor(widthScreen / getCurrentFont(&global_font_manager).size.width - 1,-1);
	}
	else{
	vdUpdateCursor(-1,0);
	}
	vdPrintCursor();
}

void resize(){
	clearScreen();
	for(int i = 0;i < index;i++){
		if(cursor.posY != heightScreen * pitch && cursor.posX != widthScreen* bytesPerPixel)
		vdPrintChar(charsInScreen[i]);
	}
	if(cursor.posY == heightScreen * pitch && cursor.posX == widthScreen* bytesPerPixel)
		scroll(1);
	else if(cursor.posX == widthScreen* bytesPerPixel)
		vdUpdateCursor(-128,1);
	else
		vdUpdateCursor(1,0);
	vdPrintCursor();
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
	memset(framebuffer,0,bytesPerPixel * heightScreen * widthScreen);
	vdSetCursor(0,0);
	vdPrintCursor();
}

void updateCharsInScreen(int lines){
	for(int i=lines * (widthScreen/getCurrentFont(&global_font_manager).size.width),j=0;i<maxCharsInScreen;i++)
		charsInScreen[j++] = charsInScreen[i];
}

void scroll(int lines) {
    int fontHeight = getCurrentFont(&global_font_manager).size.height;
    int offset = lines * fontHeight * widthScreen * bytesPerPixel;
    int frameSize = bytesPerPixel * widthScreen * (heightScreen - lines * fontHeight);
    int clearSize = bytesPerPixel * widthScreen * lines * fontHeight;
    memcpy(framebuffer, framebuffer + offset, frameSize);
    memset(framebuffer + frameSize, 0, clearSize);
	vdUpdateCursor(0,lines);
	updateCharsInScreen(lines);

}
