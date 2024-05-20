#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#define SHIFT_VALUES 2
#define MAX_SCANCODE 63

#include <stdint.h>

void updateBuffer(void);
void cleanBuffer(void);
uint8_t getKey(void);
char readLastCharacter(void);


static unsigned char scanCodes[SHIFT_VALUES][MAX_SCANCODE] = {
    {
    0,'\x1B', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    
    '\x11', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',       
    '\x12', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\x14',   
    '\x10', ' ', ' ', '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89'},
    {0,'\x1B', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',    
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',    
    '\x11', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '*:', '"', '~',        
    '\x12', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\x14',      
    '\x10', ' ', '\x3A', '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89'}  
};

enum SPECIALCHARS {
 ESCAPE            = '\x01', 
 BACKSPACE         = '\x0e',
 TAB               = '\x0f', 
 ENTER             = '\x1c', 
 CONTROL           = '\x1d',
 L_SHIFT_PRESS     = '\x2a', 
 L_SHIFT_RELEASE   = '\xaa', 
 R_SHIFT_PRESS     = '\x36',
 R_SHIFT_RELEASE   = '\xB6', 
 L_ALT             = '\x38', 
 CAPSLOCK          = '\x3A', 
};

#endif