#include <stdint.h>
#include <videoDriver.h>
#include <lib.h>
#include <process/process.h>
#include <kernelManagement.h>
#include <keyboardDriver.h>
#include <pipe/pipe.h>

#define REGS_QTY		18

void save_regs_in_buffer(void);
uint64_t* get_regs(void);

static int backup_done=0;
static uint64_t * registers;

extern int shell_pid;
extern int max_pid;

void * memset(void * destination, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--) {
		dst[length] = chr;
	}

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length) {
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 && (uint64_t)source % sizeof(uint32_t) == 0 && length % sizeof(uint32_t) == 0) {
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++) {
			d[i] = s[i];
		}
	}
	else {
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++) {
			d[i] = s[i];
		}
	}

	return destination;
}

void save_regs(void){
	backup_done = 1;
}

static char* hex_to_string(uint64_t value) {
    static char str[17];
    str[16] = '\0';
    
    char hex[] = "0123456789ABCDEF";
    
    uint64_t mask = 0xF;

    for (int i = 15; i >= 0; --i) {
        int digit = (value >> (i * 4)) & mask;
        str[15 - i] = hex[digit];
    }
    
    return str;
}

int reg_printing(void){	
	if(!backup_done) {
		return 1;
	}
	registers = get_regs();
	int count = 0;
    char * value;
    char * reg_format[] = {"RIP:    ","RFLAGS:    ", "RSP:    ", "RAX:       ", "RBP:    ", "RCX:       ", "RDX:    ", "RSI:       ", "RDI:    ", "RBX:       ", "R8:     ", "R9:        ", "R10:    ", "R11:       ", "R12:    ", "R13:       ", "R14:    ", "R15:       "};
    for(int i=0; i < REGS_QTY; i++) {
        value=hex_to_string(registers[i]);
        vd_print(reg_format[i], 0x00FFFFFF);
        vd_print("0x", 0x00FFFFFF);
        vd_print(value, 0x00FFFFFF);
        count++;
        if(count==2) {
            vd_print("\n", 0x00000000);
            count = 0;
        }
        else{
            vd_print("  ", 0x00000000);
        }
    }
    vd_print("\n", 0x00000000);
	return 0;
}

void stop_running(void) {
	for(int i = shell_pid+1; i <= max_pid; i++) {
		TPCB * current = get_pcb_by_pid(i);
		if (current == NULL) {
			continue;	
		}
		if(current->scope == FOREGROUND && current->semaphore != NULL && current->semaphore->name != NULL && count_occurrences(current->semaphore->waiting_processes, shell_pid) > 0) {
			if (is_anonymous_pipe(current->fd_r/2)) {
				force_kill_piped_processes(current->fd_r);
			}
			if (is_anonymous_pipe(current->fd_w/2)) {
				force_kill_piped_processes(current->fd_w);
			}
			forced_kill_process(current->pid);
			return;
		}
	}
}

void send_end_of_file(void) {
	for(int i = shell_pid+1; i <= max_pid; i++) {
		TPCB * current = get_pcb_by_pid(i);
		if (current == NULL) {
			continue;
		}
		if(current->scope == FOREGROUND && current->semaphore != NULL && current->semaphore->name != NULL && count_occurrences(current->semaphore->waiting_processes, shell_pid) > 0) {
			if (current->fd_r == STDIN) {
				if (current->fd_w == STDOUT) {
					kb_end_of_file();
					return;
				}
				finish_pipe(current->fd_w/2);
			}
		}
	}
}