// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <syscallDispatcher.h>
#include <interrupts.h>
#include <fonts.h>
#include <lib.h>
#include <defs.h>

#define ERRORCOL 0x00FF0000
#define COMMENTCOL 0x00FFFFFF

static void zero_division();
static void invalid_opcode();

void exception_dispatcher(int exception) {
	save_regs();
	vd_clear_screen();
	sys_hide_cursor();
	set_current_font(DEFAULT_FONT);
	for(int i=0; i<10; i++) vd_print("\n", COMMENTCOL);
	vd_print("ERROR: An exception has occurred during runtime. More information:\n\n", ERRORCOL);

	switch (exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
			break;
		case INVALID_OPCODE_ID:
			invalid_opcode();
			break;
	}
	reg_printing();
	vd_print("\n", COMMENTCOL);
	sys_ms_sleep(3, 5);
	vd_print("Press any key to recover...\n",COMMENTCOL);
	int flag=0;
	char key;
	kb_clean_buffer();
	
	while(!flag){
		flag=sys_read(STDIN, &key, 1);
	}
	vd_clear_screen();
	vd_clean_buffer();
}

static void zero_division() {
	vd_print("Arithmetic exception: division by zero\n",COMMENTCOL);
}

static void invalid_opcode(){
	vd_print("Invalid Opcode exception: command not recognised\n",COMMENTCOL);
}