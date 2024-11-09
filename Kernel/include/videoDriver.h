#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

typedef struct{
	int pos_x;
	int pos_y;
	uint32_t color;
}Cursor;

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


void intialize_video_driver();
void vd_print_char(unsigned char c);
void vd_put_pixel(uint64_t offset,uint32_t hexcolor);
void vd_print(char *characters,uint32_t hex_color);
void vd_clear_screen();
void vd_scroll(int lines);
void vd_set_cursor(int x,int y);
void vd_update_cursor(int x,int y);
void vd_delete_char();
void vd_new_line();
void vd_clean_buffer();
void vd_resize();
void vd_print_rect(int x,int y,int base,int height,uint32_t hexcolor);
void vd_print_square(int x, int y,int side,uint32_t hexcolor);
void vd_set_cursor_by_pixel(int x, int y);
void vd_set_cursor_color(uint32_t color);
void vd_print_cursor();
void vd_print_padded(const char *str, uint32_t color, int width);
int vd_screen_width();
int vd_screen_height();
void vd_print_logo(uint32_t bitmap[186][156], int bitmapWidth, int bitmapHeight);
#endif
