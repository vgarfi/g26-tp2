#ifndef __SYSCALLHANDLE_H_
#define __SYSCALLHANDLE_H_

#include <stdint.h>
#include <scheduler/scheduler.h>

int sys_set_cursor(uint64_t x, uint64_t y);
int sys_hide_cursor();
int sys_show_cursor();
int sys_print_cursor();

int sys_up_arrow_value();
int sys_left_arrow_value();
int sys_down_arrow_value();
int sys_right_arrow_value();

int sys_print_rect(int x,int y,int base,int height,uint32_t hexColor);
int sys_print_square (int x, int y,int side, uint32_t hexColor);

int sys_clear_screen();
int sys_ms_sleep(uint64_t secs, uint64_t ticks);     // rdi : ms
int sys_print_regs(void);

int sys_sound(uint64_t ms, uint64_t freq);

int sys_get_current_seconds(void);
int sys_get_current_minutes(void);
int sys_get_current_hours(void);

int sys_get_current_day(void);
int sys_get_current_month(void);
int sys_get_current_year(void);

int sys_inc_size();
int sys_dec_size();
int sys_get_zoom_level();
int sys_set_zoom_level(int zoom_level);

int sys_read(uint64_t fd, char * buf, uint64_t count);
int sys_write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor);

int sys_clean_kb_buffer(void);
int sys_is_ctrl_pressed(void);

int sys_get_current_pid(void);
int sys_exit_process(void);
int sys_create_process(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), TScope scope);
int sys_block_process(uint8_t pid);
int sys_unblock_process(uint8_t pid);
int sys_kill_process(uint8_t pid);
int sys_get_scope(uint8_t pid);
int sys_nice(uint8_t pid, uint8_t newPriority);
int sys_ps();

int sys_wait_pid(uint8_t pid);

void* sys_memory_malloc(uint64_t size);
int sys_memory_free(void* size);
int sys_memory_status(void);

int sys_yield(void);

int sys_create_sem(char* name, uint64_t initialValue);
int sys_get_sem(char* name);
int sys_post_sem(char* name);
int sys_wait_sem(char* name);
int sys_close_sem(char* name);

int sys_create_pipe(int* fds, char* name);
int sys_set_read_file_descriptor(uint8_t pid, int fd);
int sys_set_write_file_descriptor(uint8_t pid, int fd);

int sys_get_read_file_descriptor(uint8_t pid);
int sys_get_write_file_descriptor(uint8_t pid);
#endif