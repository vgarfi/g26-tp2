/**
 * @file videoDriver.h
 * @brief Definition of video driver functions and related structures.
 */

#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

/**
 * @struct Cursor
 * @brief Structure representing the cursor.
 */
typedef struct {
    int pos_x;       /**< X position of the cursor */
    int pos_y;       /**< Y position of the cursor */
    uint32_t color;  /**< Color of the cursor */
} Cursor;

/**
 * @struct vbe_mode_info_structure
 * @brief Structure representing VBE mode information.
 */
struct vbe_mode_info_structure {
    uint16_t attributes;        /**< Deprecated, only bit 7 should be of interest, indicating the mode supports a linear frame buffer */
    uint8_t window_a;           /**< Deprecated */
    uint8_t window_b;           /**< Deprecated */
    uint16_t granularity;       /**< Deprecated; used while calculating bank numbers */
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;      /**< Deprecated; used to switch banks from protected mode without returning to real mode */
    uint16_t pitch;             /**< Number of bytes per horizontal line */
    uint16_t width;             /**< Width in pixels */
    uint16_t height;            /**< Height in pixels */
    uint8_t w_char;             /**< Unused */
    uint8_t y_char;             /**< Unused */
    uint8_t planes;
    uint8_t bpp;                /**< Bits per pixel in this mode */
    uint8_t banks;              /**< Deprecated; total number of banks in this mode */
    uint8_t memory_model;
    uint8_t bank_size;          /**< Deprecated; size of a bank, almost always 64 KB but may be 16 KB */
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
    uint32_t framebuffer;       /**< Physical address of the linear frame buffer; write here to draw to the screen */
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; /**< Size of memory in the framebuffer but not being displayed on the screen */
    uint8_t reserved1[206];
} __attribute__ ((packed));

/**
 * @brief Initializes the video driver.
 */
void intialize_video_driver(void);

/**
 * @brief Prints a character on the screen.
 *
 * @param c The character to print.
 */
void vd_print_char(unsigned char c);

/**
 * @brief Puts a pixel on the screen.
 *
 * @param offset The offset of the pixel.
 * @param hex_color The color of the pixel in hexadecimal.
 */
void vd_put_pixel(uint64_t offset, uint32_t hex_color);

/**
 * @brief Prints a string on the screen.
 *
 * @param characters The string to print.
 * @param hex_color The color of the text in hexadecimal.
 */
void vd_print(char *characters, uint32_t hex_color);

/**
 * @brief Clears the screen.
 */
void vd_clear_screen(void);

/**
 * @brief Scrolls the screen by a specified number of lines.
 *
 * @param lines The number of lines to scroll.
 */
void vd_scroll(int lines);

/**
 * @brief Sets the cursor position.
 *
 * @param x The x-coordinate of the cursor.
 * @param y The y-coordinate of the cursor.
 */
void vd_set_cursor(int x, int y);

/**
 * @brief Updates the cursor position.
 *
 * @param x The x-coordinate to update.
 * @param y The y-coordinate to update.
 */
void vd_update_cursor(int x, int y);

/**
 * @brief Deletes the last character printed on the screen.
 */
void vd_delete_char(void);

/**
 * @brief Moves the cursor to a new line.
 */
void vd_new_line(void);

/**
 * @brief Cleans the screen buffer.
 */
void vd_clean_buffer(void);

/**
 * @brief Resizes the screen.
 */
void vd_resize(void);

/**
 * @brief Prints a rectangle on the screen.
 *
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param base The base length of the rectangle.
 * @param height The height of the rectangle.
 * @param hex_color The color of the rectangle in hexadecimal.
 */
void vd_print_rect(int x, int y, int base, int height, uint32_t hex_color);

/**
 * @brief Prints a square on the screen.
 *
 * @param x The x-coordinate of the square.
 * @param y The y-coordinate of the square.
 * @param side The side length of the square.
 * @param hex_color The color of the square in hexadecimal.
 */
void vd_print_square(int x, int y, int side, uint32_t hex_color);

/**
 * @brief Sets the cursor position by pixel.
 *
 * @param x The x-coordinate of the cursor.
 * @param y The y-coordinate of the cursor.
 */
void vd_set_cursor_by_pixel(int x, int y);

/**
 * @brief Sets the cursor color.
 *
 * @param color The color of the cursor.
 */
void vd_set_cursor_color(uint32_t color);

/**
 * @brief Prints the cursor on the screen.
 */
void vd_print_cursor(void);

/**
 * @brief Prints a padded string on the screen.
 *
 * @param str The string to print.
 * @param color The color of the text in hexadecimal.
 * @param width The width of the padding.
 */
void vd_print_padded(const char *str, uint32_t color, int width);

/**
 * @brief Gets the screen width.
 *
 * @return The screen width.
 */
int vd_screen_width(void);

/**
 * @brief Gets the screen height.
 *
 * @return The screen height.
 */
int vd_screen_height(void);

/**
 * @brief Prints a logo on the screen.
 *
 * @param bitmap The bitmap of the logo.
 * @param bitmapWidth The width of the bitmap.
 * @param bitmapHeight The height of the bitmap.
 */
void vd_print_logo(uint32_t bitmap[186][156], int bitmap_width, int bitmap_height);

#endif