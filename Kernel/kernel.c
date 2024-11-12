// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <fonts.h>
#include <time.h>
#include <defs.h>
#include <interrupts.h>
#include <boot.h>
#include <kernelManagement.h>
#include <process/process.h>

void load_idt(void);

uint64_t syscall_dispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax);

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t end_of_kernel_binary;
extern uint8_t end_of_kernel;

static const uint64_t PageSize = 0x1000;

extern void * sample_code_module_address;
extern void * sample_data_module_address;

void clear_bss(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * get_stack_base() {
	return (void*)(
		(uint64_t)&end_of_kernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary() {
	void * module_addresses[] = {
		sample_code_module_address,
		sample_data_module_address
	};
	load_modules(&end_of_kernel_binary, module_addresses);
	clear_bss(&bss, &end_of_kernel - &bss);
	return get_stack_base();
}

int main() {
	load_idt();
	intialize_video_driver();
	init_font_manager();
	os_logo_boot();
	initialize_management();
	request_schedule();
	vd_print("\nKERNEL EXIT", 0x00FFFFFF);
	return 0;
}