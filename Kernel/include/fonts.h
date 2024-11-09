/***************************************************
  fonts.h
****************************************************/

#include <bytes.h>

#ifndef FONT_H
#define FONT_H

#define FONTS_QUANTITY  7

#define A_FONT          0
#define B_FONT          1
#define C_FONT          2
#define D_FONT          3
#define E_FONT          4
#define F_FONT          5
#define G_FONT          6
#define H_FONT          7
#define I_FONT          8

#define DEFAULT_FONT    D_FONT

/**
 * @struct Size
 * @brief Structure representing the size of a font.
 */
typedef struct {
    int real_width;
    int width;
    int height;
} Size;

/**
 * @struct FontBitmap
 * @brief Structure representing a font bitmap.
 */
typedef struct {
    unsigned const char *bitmap;
    Size size;
} FontBitmap;

/**
 * @struct FontManager
 * @brief Structure representing the font manager.
 */
typedef struct {
    FontBitmap fonts[FONTS_QUANTITY];
    int current_font_index;
} FontManager;

/**
 * @brief Initializes the font manager.
 */
void init_font_manager();

/**
 * @brief Sets the current font.
 *
 * @param index The index of the font to set as current.
 * @return 0 on success, -1 on failure.
 */
int set_current_font(int index);

/**
 * @brief Gets the current font.
 *
 * @return The current FontBitmap.
 */
FontBitmap get_current_font();

/**
 * @brief Increases the font size.
 *
 * @return 0 on success, -1 on failure.
 */
int size_up(void);

/**
 * @brief Decreases the font size.
 *
 * @return 0 on success, -1 on failure.
 */
int size_down(void);

/**
 * @brief Gets the current zoom level.
 *
 * @return The current zoom level.
 */
int get_zoom();

/**
 * @brief Sets the zoom level.
 *
 * @param zoom_level The zoom level to set.
 * @return 0 on success, -1 on failure.
 */
int set_zoom(int zoom_level);

#endif