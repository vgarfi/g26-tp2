// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <videoDriver.h>
#include <defs.h>
#include <fonts.h>
#include <lib.h>
#include <boot.h>
#include <string.h>

#define MAXCHARSINSCREEN 10880	// chars per row * chars per column (with minimum size)
#define GREY 0x00F0F0F0
#define BLACK 0x00000000

typedef struct vbe_mode_info_structure * VBEInfoPtr;
VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;
Cursor cursor = {0, 0,GREY};
uint8_t * framebuffer;
uint16_t widthScreen;
uint16_t heightScreen;
uint16_t pitch;
uint8_t  bytesPerPixel;
static uint32_t fgColor = GREY;
const uint32_t bgColor = BLACK;
char charsInScreen[MAXCHARSINSCREEN];
uint32_t colorsInScreen[MAXCHARSINSCREEN];
static int index;
static int scrollkb_update_buffer;

void intialize_video_driver(){
	framebuffer = (uint8_t *)(uintptr_t) VBE_mode_info->framebuffer;
	widthScreen = 	VBE_mode_info->width;
	heightScreen = VBE_mode_info->height;
	pitch = VBE_mode_info->pitch;
	bytesPerPixel = VBE_mode_info->bpp/BYTE_LENGHT;
	memset(charsInScreen,' ',MAXCHARSINSCREEN);
	memset(colorsInScreen,0,4*MAXCHARSINSCREEN);
	scrollkb_update_buffer = 1;
	index = 0;
}

void vdPrintLine(uint64_t offset,uint32_t fgColor,uint32_t bgColor ,uint8_t mask,int limit,int step){
	uint64_t off = offset;
	uint32_t hex_color;
	for(int i=0; i < limit; i++,off+=step){
		if (mask & (1 << (BYTE_LENGHT - 1 - i))) {
			hex_color = fgColor;
		} 
		else{
			hex_color = bgColor;
		}
		vd_put_pixel(off,hex_color);
	}
}

void vd_set_cursor_color(uint32_t hexcolor){
	cursor.color = hexcolor;
}

void vd_update_cursor(int x, int y){
	int offsetX = x * bytesPerPixel * (get_current_font().size.real_width);
	int offsetY = y * pitch * (get_current_font().size.height); 

	if(cursor.pos_y + offsetY >= 0){
		if (cursor.pos_x + offsetX >= widthScreen*bytesPerPixel)
		{
			offsetX = 0;
			cursor.pos_x = 0;
			offsetY += (pitch * get_current_font().size.height);
		}
		else if(cursor.pos_x + offsetX < 0){
			offsetX = 0;
			cursor.pos_x = (widthScreen - get_current_font().size.real_width) * bytesPerPixel;
			offsetY -= pitch * get_current_font().size.height;
		}

		if (cursor.pos_y + offsetY >= heightScreen * pitch)
		{
			vd_scroll(1);
			offsetY += -pitch * get_current_font().size.height;
			
		}
		else if (cursor.pos_y + offsetY < 0)
		{
			offsetY = 0;
		}
		cursor.pos_x += offsetX;
		cursor.pos_y += offsetY;
	}

}

void vd_print_cursor(){
	if (cursor.pos_x + (get_current_font().size.real_width*bytesPerPixel) >= widthScreen*bytesPerPixel)
	{
		vd_update_cursor(1,0);
	}
	if (cursor.pos_y + (get_current_font().size.height*pitch) >= heightScreen*pitch)
	{
		vd_scroll(1);
		cursor.pos_y -= pitch *get_current_font().size.height;
	}
	vd_print_rect(cursor.pos_x/bytesPerPixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,cursor.color);
}

void vd_set_cursor_by_pixel(int x, int y){
	int pos_x = x * bytesPerPixel;
	int pos_y = y * pitch;
	if(pos_x < widthScreen*bytesPerPixel && pos_x >= 0 && pos_y >= 0 && pos_y < pitch * heightScreen){
		cursor.pos_x = pos_x;
		cursor.pos_y = pos_y;
	}
}

void vd_set_cursor(int x, int y){
	int pos_x = x * bytesPerPixel * get_current_font().size.real_width;
	int pos_y = y * pitch * get_current_font().size.height;
	if(pos_x < widthScreen*bytesPerPixel && pos_x >= 0 && pos_y >= 0 && pos_y < pitch * heightScreen){
		cursor.pos_x = pos_x;
		cursor.pos_y = pos_y;
	}
}

void vd_new_line(){
	vd_print_rect(cursor.pos_x/bytesPerPixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
	cursor.pos_x = 0;
	vd_update_cursor(0,1);
	vd_print_cursor();
}

void vd_put_pixel(uint64_t offset,uint32_t hex_color){
	framebuffer[offset]     =  (hex_color) & 0xFF;
    framebuffer[offset+1]   =  (hex_color >> BYTE_LENGHT) & 0xFF; 
    framebuffer[offset+2]   =  (hex_color >> TWO_BYTE_LENGHT) & 0xFF;
}

void vd_print_char(unsigned char c) {
	FontBitmap fontBitMap = get_current_font();
	unsigned const char* bitmap = fontBitMap.bitmap;
	int width = fontBitMap.size.width;
	int height = fontBitMap.size.height;

	uint64_t offset = cursor.pos_x + cursor.pos_y;

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
	vd_update_cursor(1,0);
	vd_print_cursor();
}

void vd_print(char *characters,uint32_t hex_color){
	fgColor = hex_color;
	for(int i=0;characters[i] != 0;i++){
		char c = characters[i];

		if(c == '\n'){
			colorsInScreen[index] = BLACK;
			charsInScreen[index++] = '\n';
			vd_new_line();
		}

		else if(c == '\b'){
			vd_delete_char();
			if(index != 0)
				--index;
			colorsInScreen[index] = BLACK;
			charsInScreen[index] = ' ';
		} else if (c == '\t') {
			int spacesToNextTabStop = 4 - (cursor.pos_x / (bytesPerPixel * get_current_font().size.real_width)) % 4;
            for (int j = 0; j < spacesToNextTabStop; j++) {
                vd_print_char(' ');
                colorsInScreen[index] = hex_color;
                charsInScreen[index++] = ' ';
            }
		}
		else{
		vd_print_char(c);
		colorsInScreen[index] = hex_color;
		charsInScreen[index++] = c;
		}
	}
}

void vd_delete_char(){
	vd_print_rect(cursor.pos_x/bytesPerPixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
	vd_update_cursor(-1,0);
	vd_print_rect(cursor.pos_x/bytesPerPixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
	vd_print_cursor();
}

void vd_resize(){
	vd_clear_screen();
	scrollkb_update_buffer = 0;
	char c;
	for(int j=0;j<index;j++){
		c = charsInScreen[j];
		if(c == '\n'){
			vd_new_line();
		}
		else{
			fgColor = colorsInScreen[j];	
			vd_print_char(c);
			}	
	}
	scrollkb_update_buffer = 1;
}

void vd_clear_screen(){
	memset(framebuffer,0,bytesPerPixel * heightScreen * widthScreen);
	vd_set_cursor(0,0);
}

void vd_clean_buffer(){
	memset(charsInScreen,' ',MAXCHARSINSCREEN);
	memset(colorsInScreen,0,4*MAXCHARSINSCREEN);
	index = 0;
}

void updateCharsInScreen(int lines){
	for(int i=lines * (widthScreen/get_current_font().size.real_width),j=0;i<MAXCHARSINSCREEN;i++){
		colorsInScreen[j] = colorsInScreen[i];
		charsInScreen[j++] = charsInScreen[i];
	}
}

void vd_scroll(int lines) {
    int fontHeight = get_current_font().size.height;
    int offset = lines * fontHeight * widthScreen * bytesPerPixel;
    int frameSize = bytesPerPixel * widthScreen * (heightScreen - lines * (fontHeight));
    int clearSize = bytesPerPixel * widthScreen * lines * fontHeight;
    memcpy(framebuffer, framebuffer + offset, frameSize);
    memset(framebuffer + frameSize, 0, clearSize);
	if(scrollkb_update_buffer == 1 && index >= MAXCHARSINSCREEN){
		if(index - lines * (widthScreen/get_current_font().size.real_width) >=0){
			index -= lines * (widthScreen/get_current_font().size.real_width);
		}
		updateCharsInScreen(lines);
	}
}

void vd_print_rect(int x,int y,int base, int height, uint32_t hex_color){
	uint64_t offsetX = x * bytesPerPixel;
	uint64_t pos_x = offsetX;
	uint64_t offsetY = y * pitch;
	for(int y=0;y < height;y++,offsetY += pitch) {
		for(int x = 0,offsetX = pos_x; x < base;x++, offsetX += bytesPerPixel)
			vd_put_pixel(offsetX + offsetY,hex_color);
	}
}

void vd_print_square(int x, int y,int side,uint32_t hex_color){
	vd_print_rect(x,y,side,side,hex_color);
}

void vd_print_padded(const char *str, uint32_t color, int width) {
    vd_print((char *)str, color);
    int padding = width - strlen(str);
    for (int i = 0; i < padding; i++) {
        vd_print(" ", color);
    }
}

int vd_screen_width() {
	return widthScreen;
}

int vd_screen_height() {
	return heightScreen;
}


void vd_print_logo(uint32_t bitmap[186][156], int bitmapWidth, int bitmapHeight) {
	if (bitmapWidth <= 0 || bitmapHeight <= 0) {
		return;
	}

	int startX = (widthScreen - bitmapWidth) / 2;
	int startY = (heightScreen - bitmapHeight) / 2;

	for (int x = 0; x < bitmapWidth; x++) {
		for (int y = 0; y < bitmapHeight; y++) {
			uint32_t hex_color = bitmap[x][y];

			int pos_x = (startX + x) * bytesPerPixel;
			int pos_y = (startY + y) * pitch;

			if (pos_x < widthScreen * bytesPerPixel && pos_y < heightScreen * pitch) {
				vd_put_pixel(pos_x + pos_y, hex_color);
			}
		}
	}
}