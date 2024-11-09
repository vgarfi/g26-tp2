#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#define SHIFT_VALUES 2
#define MAX_SCANCODE 69

#include <stdint.h>

void updateBuffer(void);
void kbcleanBuffer(void);
void kbInsertNewLine(void);
void kbEndOfFile(void);
uint8_t get_key(void);
uint8_t kbUpArrowValue(void);
uint8_t kbLeftArrowValue(void);
uint8_t kbDownArrowValue(void);
uint8_t kbRightArrowValue(void);
void initialize_keyboard(void);


int kbisBufferEmpty();
unsigned char kbreadBuf(void);
int kbctrlPressed(void);

enum SPECIALCHARS {
 CONTROL           = 0x1d,
 CONTROL_RELEASED = 0x9D,
 L_SHIFT_PRESS     = 0x2a, 
 L_SHIFT_RELEASE   = 0xaa, 
 R_SHIFT_PRESS     = 0x36,
 R_SHIFT_RELEASE   = 0xB6, 
 L_ALT             = 0x38,
 UP_ARROW          = 0x48,
 LEFT_ARROW        = 0x4B,
 DOWN_ARROW        = 0x50,
 RIGHT_ARROW       = 0x4D,
 C                 = 0X2E,
 D                 = 0x20
};

#endif