#include <synchro/synchro.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <defs.h>

#define MAXSIZE 128

#define UP_ARROW_VAL        0xE0
#define LEFT_ARROW_VAL      0xE1
#define DOWN_ARROW_VAL      0xE2
#define RIGHT_ARROW_VAL     0xE3

#define KEYBOARD_SEM        "a_kb"

static unsigned char buffer[MAXSIZE] = {0};
static int buffer_pos = 0;
static int shift = 0;
static int dataStatus = 0;
static int ctrl_pressed=0;

void initialize_keyboard(void){
    create_sem(KEYBOARD_SEM, 0);
}

static unsigned char scancodesChars[SHIFT_VALUES][MAX_SCANCODE] = {
    {
    0,'\x1B', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',    
    '\x11', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',       
    '\x12', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\x14',   
    '*', '\x10', ' ', '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89'},
    {0,'\x1B', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',    
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',    
    '\x11', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',        
    '\x12', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\x14',      
    '*', '\x10', ' ', '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89'}
};

int shift_handler(uint8_t key){
    switch(key) {
        case L_SHIFT_PRESS:
        case R_SHIFT_PRESS:
            shift = 1;
            return 1; 
            
        case L_SHIFT_RELEASE:
        case R_SHIFT_RELEASE:
            shift = 0;
            return 1;

        default:
            return 0; 
    }
}

uint8_t isArrow (uint8_t key) {
    switch (key)
    {
    case UP_ARROW:
        return UP_ARROW_VAL;
    
    case LEFT_ARROW:
        return LEFT_ARROW_VAL;

    case DOWN_ARROW:
        return DOWN_ARROW_VAL;
    
    case RIGHT_ARROW:
        return RIGHT_ARROW_VAL;

    default:
        return 0;
    }    
}

uint8_t kb_up_arrow_value() {
    return UP_ARROW_VAL;
}

uint8_t kb_left_arrow_value() {
    return LEFT_ARROW_VAL;
}

uint8_t kb_down_arrow_value() {
    return DOWN_ARROW_VAL;
}

uint8_t kb_right_arrow_value() {
    return RIGHT_ARROW_VAL;
}

void kb_update_buffer() {
    uint8_t scancode = kb_get_key();
    uint8_t arrow_value = isArrow(scancode);

    if(scancode == L_ALT) {
        save_regs();
    }
    else if(scancode==CONTROL) {
        ctrl_pressed=1;
    }
    
    else if(scancode==CONTROL_RELEASED){
        ctrl_pressed=0;
    }

    else if (ctrl_pressed) {    
        if(scancode == C) {
            stop_running();
            ctrl_pressed = 0;
        }
        else if (scancode == D) {
            send_end_of_file();
            ctrl_pressed = 0;
        }
    }

    if(arrow_value || (!shift_handler(scancode) && scancode < MAX_SCANCODE)) { // We add the characters, with their corresponding modification for a shift
        dataStatus = 1;
        char c = (arrow_value != 0)? arrow_value : scancodesChars[shift][scancode];
        buffer[buffer_pos++] = c;
        post_sem(KEYBOARD_SEM);
        if (buffer_pos >= MAXSIZE) {
            buffer_pos = 0;
        }
    }
}

// TODO ver esto
void kb_insert_new_line(void) {
    buffer[buffer_pos++] = '\n';
    post_sem(KEYBOARD_SEM);
}

int kb_ctrl_pressed(){
    return ctrl_pressed;
}

int kb_is_buffer_empty(){
    return buffer_pos == 0;
}

void kb_clean_buffer(){
    buffer_pos = 0;
}

void kb_end_of_file(){
    buffer[buffer_pos++] = EOF;
}

unsigned char kb_read_buf () {
    wait_sem(KEYBOARD_SEM);
    if(kb_is_buffer_empty()) {
        return 0;
    }
    
    char ans = buffer[0];
    for(int i=0; i<buffer_pos-1; i++)
        buffer[i]=buffer[i+1];

    buffer_pos--;
    return ans;
}   