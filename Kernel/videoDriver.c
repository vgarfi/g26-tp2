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
uint16_t width_screen;
uint16_t height_screen;
uint16_t pitch;
uint8_t  bytes_per_pixel;
static uint32_t fg_color = GREY;
const uint32_t bg_color = BLACK;
char chars_in_screen[MAXCHARSINSCREEN];
uint32_t colors_in_screen[MAXCHARSINSCREEN];
static int index;
static int scrollkb_update_buffer;

void intialize_video_driver(){
	framebuffer = (uint8_t *)(uintptr_t) VBE_mode_info->framebuffer;
	width_screen = 	VBE_mode_info->width;
	height_screen = VBE_mode_info->height;
	pitch = VBE_mode_info->pitch;
	bytes_per_pixel = VBE_mode_info->bpp/BYTE_LENGHT;
	memset(chars_in_screen,' ',MAXCHARSINSCREEN);
	memset(colors_in_screen,0,4*MAXCHARSINSCREEN);
	scrollkb_update_buffer = 1;
	index = 0;
}

void vd_print_line(uint64_t offset,uint32_t fg_color,uint32_t bg_color ,uint8_t mask,int limit,int step){
	uint64_t off = offset;
	uint32_t hex_color;
	for(int i=0; i < limit; i++,off+=step){
		if (mask & (1 << (BYTE_LENGHT - 1 - i))) {
			hex_color = fg_color;
		} 
		else{
			hex_color = bg_color;
		}
		vd_put_pixel(off,hex_color);
	}
}

void vd_set_cursor_color(uint32_t hex_color){
	cursor.color = hex_color;
}

void vd_update_cursor(int x, int y){
	int offsetX = x * bytes_per_pixel * (get_current_font().size.real_width);
	int offsetY = y * pitch * (get_current_font().size.height); 

	if(cursor.pos_y + offsetY >= 0){
		if (cursor.pos_x + offsetX >= width_screen*bytes_per_pixel)
		{
			offsetX = 0;
			cursor.pos_x = 0;
			offsetY += (pitch * get_current_font().size.height);
		}
		else if(cursor.pos_x + offsetX < 0){
			offsetX = 0;
			cursor.pos_x = (width_screen - get_current_font().size.real_width) * bytes_per_pixel;
			offsetY -= pitch * get_current_font().size.height;
		}

		if (cursor.pos_y + offsetY >= height_screen * pitch)
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
	if (cursor.pos_x + (get_current_font().size.real_width*bytes_per_pixel) >= width_screen*bytes_per_pixel)
	{
		vd_update_cursor(1,0);
	}
	if (cursor.pos_y + (get_current_font().size.height*pitch) >= height_screen*pitch)
	{
		vd_scroll(1);
		cursor.pos_y -= pitch *get_current_font().size.height;
	}
	vd_print_rect(cursor.pos_x/bytes_per_pixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,cursor.color);
}

void vd_set_cursor_by_pixel(int x, int y){
	int pos_x = x * bytes_per_pixel;
	int pos_y = y * pitch;
	if(pos_x < width_screen*bytes_per_pixel && pos_x >= 0 && pos_y >= 0 && pos_y < pitch * height_screen){
		cursor.pos_x = pos_x;
		cursor.pos_y = pos_y;
	}
}

void vd_set_cursor(int x, int y){
	int pos_x = x * bytes_per_pixel * get_current_font().size.real_width;
	int pos_y = y * pitch * get_current_font().size.height;
	if(pos_x < width_screen*bytes_per_pixel && pos_x >= 0 && pos_y >= 0 && pos_y < pitch * height_screen){
		cursor.pos_x = pos_x;
		cursor.pos_y = pos_y;
	}
}

void vd_new_line(){
	vd_print_rect(cursor.pos_x/bytes_per_pixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
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
			vd_print_line(offset,fg_color,bg_color,bitmap[y_pos + (c-31) * height],BYTE_LENGHT,bytes_per_pixel);
		}
	}
	else {
		for (int y_pos = 0, pY = 0; y_pos < height*2; y_pos+=2, pY++,offset+=VBE_mode_info->pitch) {
			vd_print_line(offset,fg_color,bg_color,bitmap[y_pos + (c-31) * height*2],BYTE_LENGHT,bytes_per_pixel);
			vd_print_line(offset+(width*bytes_per_pixel/2),fg_color,bg_color,bitmap[y_pos + (c-31) * height*2 + 1],BYTE_LENGHT,bytes_per_pixel);
		}
	}
	vd_update_cursor(1,0);
	vd_print_cursor();
}

void vd_print(char *characters,uint32_t hex_color){
	fg_color = hex_color;
	for(int i=0;characters[i] != 0;i++){
		char c = characters[i];

		if(c == '\n'){
			colors_in_screen[index] = BLACK;
			chars_in_screen[index++] = '\n';
			vd_new_line();
		}

		else if(c == '\b'){
			vd_delete_char();
			if(index != 0)
				--index;
			colors_in_screen[index] = BLACK;
			chars_in_screen[index] = ' ';
		} else if (c == '\t') {
			int spacesToNextTabStop = 4 - (cursor.pos_x / (bytes_per_pixel * get_current_font().size.real_width)) % 4;
            for (int j = 0; j < spacesToNextTabStop; j++) {
                vd_print_char(' ');
                colors_in_screen[index] = hex_color;
                chars_in_screen[index++] = ' ';
            }
		}
		else{
		vd_print_char(c);
		colors_in_screen[index] = hex_color;
		chars_in_screen[index++] = c;
		}
	}
}

void vd_delete_char(){
	vd_print_rect(cursor.pos_x/bytes_per_pixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
	vd_update_cursor(-1,0);
	vd_print_rect(cursor.pos_x/bytes_per_pixel,cursor.pos_y/pitch,get_current_font().size.real_width,get_current_font().size.height,BLACK);
	vd_print_cursor();
}

void vd_resize(){
	vd_clear_screen();
	scrollkb_update_buffer = 0;
	char c;
	for(int j=0;j<index;j++){
		c = chars_in_screen[j];
		if(c == '\n'){
			vd_new_line();
		}
		else{
			fg_color = colors_in_screen[j];	
			vd_print_char(c);
			}	
	}
	scrollkb_update_buffer = 1;
}

void vd_clear_screen(){
	memset(framebuffer,0,bytes_per_pixel * height_screen * width_screen);
	vd_set_cursor(0,0);
}

void vd_clean_buffer(){
	memset(chars_in_screen,' ',MAXCHARSINSCREEN);
	memset(colors_in_screen,0,4*MAXCHARSINSCREEN);
	index = 0;
}

void update_chars_in_screen(int lines){
	for(int i=lines * (width_screen/get_current_font().size.real_width),j=0;i<MAXCHARSINSCREEN;i++){
		colors_in_screen[j] = colors_in_screen[i];
		chars_in_screen[j++] = chars_in_screen[i];
	}
}

void vd_scroll(int lines) {
    int fontHeight = get_current_font().size.height;
    int offset = lines * fontHeight * width_screen * bytes_per_pixel;
    int frameSize = bytes_per_pixel * width_screen * (height_screen - lines * (fontHeight));
    int clearSize = bytes_per_pixel * width_screen * lines * fontHeight;
    memcpy(framebuffer, framebuffer + offset, frameSize);
    memset(framebuffer + frameSize, 0, clearSize);
	if(scrollkb_update_buffer == 1 && index >= MAXCHARSINSCREEN){
		if(index - lines * (width_screen/get_current_font().size.real_width) >=0){
			index -= lines * (width_screen/get_current_font().size.real_width);
		}
		update_chars_in_screen(lines);
	}
}

void vd_print_rect(int x,int y,int base, int height, uint32_t hex_color){
	uint64_t offsetX = x * bytes_per_pixel;
	uint64_t pos_x = offsetX;
	uint64_t offsetY = y * pitch;
	for(int y=0;y < height;y++,offsetY += pitch) {
		for(int x = 0,offsetX = pos_x; x < base;x++, offsetX += bytes_per_pixel)
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
	return width_screen;
}

int vd_screen_height() {
	return height_screen;
}


void vd_print_logo(uint32_t bitmap[186][156], int bitmapWidth, int bitmapHeight) {
	if (bitmapWidth <= 0 || bitmapHeight <= 0) {
		return;
	}

	int startX = (width_screen - bitmapWidth) / 2;
	int startY = (height_screen - bitmapHeight) / 2;

	for (int x = 0; x < bitmapWidth; x++) {
		for (int y = 0; y < bitmapHeight; y++) {
			uint32_t hex_color = bitmap[x][y];

			int pos_x = (startX + x) * bytes_per_pixel;
			int pos_y = (startY + y) * pitch;

			if (pos_x < width_screen * bytes_per_pixel && pos_y < height_screen * pitch) {
				vd_put_pixel(pos_x + pos_y, hex_color);
			}
		}
	}
}