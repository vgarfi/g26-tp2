#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define SHIFT_VALUES 2
#define MAX_SCANCODE 69

#include <stdint.h>

/**
 * @brief Initializes the keyboard.
 */
void initialize_keyboard(void);

/**
 * @brief Updates the keyboard buffer.
 */
void kb_update_buffer(void);

/**
 * @brief Checks if the keyboard buffer is empty.
 *
 * @return 1 if the buffer is empty, 0 otherwise.
 */
int kb_is_buffer_empty(void);

/**
 * @brief Reads a character from the keyboard buffer.
 *
 * @return The character read from the buffer.
 */
unsigned char kb_read_buf(void);

/**
 * @brief Reads a character from the keyboard buffer without blocking the process.
 *
 * @return The character read from the buffer.
 */
unsigned char kb_read_buf_no_block(void);

/**
 * @brief Cleans the keyboard buffer.
 */
void kb_clean_buffer(void);

/**
 * @brief Inserts a new line in the keyboard buffer.
 */
void kb_insert_new_line(void);

/**
 * @brief Marks the end of file in the keyboard buffer.
 */
void kb_end_of_file(void);

/**
 * @brief Gets the current key from the keyboard.
 *
 * @return The current key.
 */
uint8_t kb_get_key(void);

/**
 * @brief Gets the value of the up arrow key.
 *
 * @return The value of the up arrow key.
 */
uint8_t kb_up_arrow_value(void);

/**
 * @brief Gets the value of the left arrow key.
 *
 * @return The value of the left arrow key.
 */
uint8_t kb_left_arrow_value(void);

/**
 * @brief Gets the value of the down arrow key.
 *
 * @return The value of the down arrow key.
 */
uint8_t kb_down_arrow_value(void);

/**
 * @brief Gets the value of the right arrow key.
 *
 * @return The value of the right arrow key.
 */
uint8_t kb_right_arrow_value(void);

/**
 * @brief Checks if the control key is pressed.
 *
 * @return 1 if the control key is pressed, 0 otherwise.
 */
int kb_ctrl_pressed(void);

/**
 * @enum SPECIALCHARS
 * @brief Enumeration of special characters.
 */
enum SPECIALCHARS {
    CONTROL           = 0x1d,
    CONTROL_RELEASED  = 0x9D,
    L_SHIFT_PRESS     = 0x2a, 
    L_SHIFT_RELEASE   = 0xaa, 
    R_SHIFT_PRESS     = 0x36,
    R_SHIFT_RELEASE   = 0xB6, 
    L_ALT             = 0x38,
    UP_ARROW          = 0x48,
    LEFT_ARROW        = 0x4B,
    DOWN_ARROW        = 0x50,
    RIGHT_ARROW       = 0x4D,
    C                 = 0x2E,
    D                 = 0x20
};

#endif