// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <defs.h>
#include <videoDriver.h>
#include <time.h>
#include <keyboardDriver.h>
#include <scheduler/scheduler.h>
#include <pipe/pipe.h>
#include <synchro/synchro.h>
#include <interrupts.h>
#include <lib.h>
#include <stdio.h>
#include <syscallDispatcher.h>
#include <kernelManagement.h>
#include <speaker.h>
#include <fonts.h>

extern MemoryManagerADT memory_manager;

#define HANDLER_SIZE 54
#define MEMORY_COLUMN_WIDTH 25
#define BLOCKS_COLUMN_WIDTH 25

static int (*syscall_handlers[])()={
    // Syscalls de Arqui
    sys_read, sys_write, sys_print_regs, sys_inc_size, sys_dec_size, sys_get_zoom_level, sys_set_zoom_level, sys_up_arrow_value, sys_left_arrow_value, sys_down_arrow_value,
    sys_right_arrow_value, sys_clear_screen, sys_print_square, sys_print_rect, sys_set_cursor, sys_sound, sys_ms_sleep, sys_hide_cursor,
    sys_show_cursor, sys_print_cursor, sys_get_current_seconds, sys_get_current_minutes, sys_get_current_hours, sys_get_current_day,
    sys_get_current_month, sys_get_current_year, sys_is_ctrl_pressed, sys_clean_kb_buffer,
    // Syscalls de SO
    sys_get_current_pid, sys_exit_process, sys_create_process, (int (*)())sys_block_process, (int (*)())sys_unblock_process, (int (*)())sys_kill_process, (int (*)())sys_nice, sys_ps,
    (int (*)())sys_memory_malloc, sys_memory_free, sys_memory_status,
    sys_yield, sys_create_sem, sys_get_sem, sys_post_sem, sys_wait_sem, sys_close_sem,
    (int (*)())sys_wait_pid,
    sys_create_pipe, (int (*)())sys_set_read_file_descriptor, (int (*)())sys_set_write_file_descriptor, (int (*)())sys_get_read_file_descriptor, (int (*)())sys_get_write_file_descriptor,
    (int (*)())sys_get_scope, sys_read_no_block,
    sys_get_shared_memory
};

uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){         
    // int handlerSize = sizeof(syscall_handlers)/sizeof(syscall_handlers[0]);
    if(rax >= HANDLER_SIZE)
        return -1;

    return syscall_handlers[rax](rdi,rsi,rdx,r10,r8);
}

int sys_read(uint64_t fd, char * buf, uint64_t count) {
    if (fd == STDIN) {
        uint64_t size_read = 0;
        char last_read = '\0';
        while(size_read != count){
                last_read = kb_read_buf();
                buf[size_read++] = last_read;
        }
        return size_read == count? count : size_read;    // If we return size_read-1 it means we stopped at '\n'    
    }
    return read_pipe(fd/2, buf, count);
}


int sys_read_no_block(uint64_t fd, char * buf, uint64_t count) {
    if (fd == STDIN) {
        uint64_t size_read = 0;
        char last_read = '\0';
        while(size_read != count){
                last_read = kb_read_buf_no_block();
                buf[size_read++] = last_read;
        }
        return size_read == count? count : size_read;    // If we return size_read-1 it means we stopped at '\n'    
    }
    return 0;
}

int sys_write(uint64_t fd, char * buf, uint64_t count, uint64_t hex_color){
    int i;
    char to_print[2] = {0,0};

    if (fd == STDOUT) {
        for(i=0; i < count; i++) {
            to_print[0] = buf[i];
            vd_print(to_print, hex_color); 
        }
        return i;
    }
    return write_pipe(fd/2, buf, count);
}

int sys_inc_size(){
    int zoom_fail = size_up();
    if(!zoom_fail)
        vd_resize();
    return zoom_fail;
}

int sys_dec_size(){
    int zoom_fail = size_down();
    if(!zoom_fail)
        vd_resize();
    return zoom_fail;
}

int sys_get_zoom_level(){
    return get_zoom();
}

int sys_set_zoom_level(int zoom_level) {
    return set_zoom(zoom_level);
}

int sys_up_arrow_value() {    
    return kb_up_arrow_value();
}

int sys_left_arrow_value() {
    return kb_left_arrow_value();
}

int sys_down_arrow_value() {
    return kb_down_arrow_value();
}

int sys_right_arrow_value() {
    return kb_right_arrow_value();
}

int sys_clear_screen() {
    vd_clear_screen();
    vd_clean_buffer();
    return 0;
}

int sys_print_rect(int x,int y,int base,int height,uint32_t hex_color) {
    vd_print_rect(x, y, base, height, hex_color);
    return 0;
}

int sys_print_square (int x, int y,int side, uint32_t hex_color){
    vd_print_square(x, y ,side, hex_color);
    return 0;
}

int sys_set_cursor(uint64_t x, uint64_t y) {
    vd_set_cursor(x, y);
    return 0;
}

/** registers are stored in a buffer of 18 qwords in the next order:
 *  RIP RFLAGS RSP RAX RBX RCX RDX RSI RDI RBP R8 R9 R10 R11 R12 R13 R14 R15
 */
int sys_print_regs(){
    return reg_printing();
}

int sys_sound(uint64_t ms, uint64_t freq){
    beep(ms, freq);
    return 0;
}

// rdi = seconds, rsi = ms
int sys_ms_sleep(uint64_t secs, uint64_t ticks){
    int seconds_to_ticks = secs*18, ms_to_ticks=ticks;
    int total_ticks = seconds_to_ticks + ms_to_ticks;
    sleep(total_ticks);
    return 0;
}

int sys_hide_cursor(){
    vd_set_cursor_color(0x00000000);
    return 0;
}

int sys_show_cursor(){
    vd_set_cursor_color(0x00F0F0F0);
    return 0;
}

int sys_print_cursor(){
    vd_print_cursor();
    return 0;
}

int sys_get_current_seconds(void){
    return rtc_get_seconds();
}

int sys_get_current_minutes(void){
    return rtc_get_minutes();
}

int sys_get_current_hours(void){
    return rtc_get_hour();
}

int sys_get_current_day(void){
    return rtc_get_day();
}

int sys_get_current_month(void){
    return rtc_get_month();
}

int sys_get_current_year(void){
    return rtc_get_year();
}

int sys_is_ctrl_pressed(){
    return kb_ctrl_pressed();
}

int sys_clean_kb_buffer(){
    kb_clean_buffer();
    return 0;
}

int sys_get_current_pid(){
    return get_current_pid();
}

int sys_exit_process(){
    return kill_process(sys_get_current_pid());
}

int sys_create_process(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), TScope scope){
    return create_process(name, argc, argv, 1, code, scope);
}

int sys_block_process(uint8_t pid){
    return block_process(pid);
}

int sys_unblock_process(uint8_t pid){
    return unblock_process(pid);
}

int sys_kill_process(uint8_t pid) {
    return forced_kill_process(pid);
}

int sys_get_scope(uint8_t pid) {
    return get_process_scope(pid);
}

int sys_nice(uint8_t pid, uint8_t new_priority){
    return change_priority(pid, new_priority);
}

int sys_ps(void){
    return processes_information();
}
void* sys_memory_malloc(uint64_t size){
    return malloc_mm(memory_manager, size);
}

int sys_memory_free(void* ptr) {
    free_mm(memory_manager, ptr);
    return 0;
}

int sys_memory_status(void) {
    int zoom_level = get_zoom();
    set_zoom(2);
    MemoryDiagnostic diagnostic = get_diagnostic_mm(memory_manager);
    char buffer[64];

    vd_print("\n", 0x00FFFFFF);
    vd_print_padded("Type", 0x00FFFFFF, MEMORY_COLUMN_WIDTH);
    vd_print_padded("Memory (bytes)", 0x00FFFFFF, MEMORY_COLUMN_WIDTH);
    vd_print_padded("Blocks", 0x00FFFFFF, BLOCKS_COLUMN_WIDTH);
    vd_print("\n", 0x00FFFFFF);

    vd_print_padded("TOTAL", 0x00FFC90E, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.total_memory, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.total_blocks, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, BLOCKS_COLUMN_WIDTH);

    vd_print("\n", 0x00FFFFFF);

    vd_print_padded("USED", 0x00FF440B, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.used_memory, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.used_blocks, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, BLOCKS_COLUMN_WIDTH);

    vd_print("\n", 0x00FFFFFF);

    vd_print_padded("FREE", 0x003CBA14, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.free_memory, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, MEMORY_COLUMN_WIDTH);

    itoa64(diagnostic.free_blocks, buffer, 10);
    vd_print_padded(buffer, 0x00FFFFFF, BLOCKS_COLUMN_WIDTH);

    vd_print("\n", 0x00FFFFFF);
    set_zoom(zoom_level);
    return 0;
}

int sys_yield(void){
    return yield_process();
}

int sys_create_sem(char* name, uint64_t initial_value){
    TSemaphore* result = create_sem(name, initial_value);
    if (result == NULL) {
        return -1;
    }
    return 0;
}
int sys_get_sem(char* name){
    TSemaphore* result = get_sem(name);
    if (result == NULL) {
        return -1;
    }
    return EXIT_SUCCESS;
}
int sys_post_sem(char* name){
    post_sem(name);
    return EXIT_SUCCESS;
}
int sys_wait_sem(char* name){
    wait_sem(name);
    return EXIT_SUCCESS;
}
int sys_close_sem(char* name){
    delete_sem(name);
    return EXIT_SUCCESS;
}

int sys_wait_pid(uint8_t pid){
    wait_process_by_pid(pid);
    return EXIT_SUCCESS;
}

int sys_create_pipe(int* fds, char* name) {
    return create_pipe(fds, name);
}

int sys_set_read_file_descriptor(uint8_t pid, int fd) {
    return set_read_filedescriptor(pid, fd);
}

int sys_set_write_file_descriptor(uint8_t pid, int fd) {
    return set_write_filedescriptor(pid, fd);
}

int sys_get_read_file_descriptor(uint8_t pid) {
    return get_read_filedescriptor(pid);
}

int sys_get_write_file_descriptor(uint8_t pid) {
    return get_write_filedescriptor(pid);
}

void* sys_get_shared_memory(uint8_t id) {
    return get_shared_memory_block(id);
}