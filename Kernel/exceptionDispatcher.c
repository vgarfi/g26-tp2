#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6
#include <videoDriver.h>
#include <keyboard.h>
#include <interrupts.h>
#include <interrupts.h>

int nanosleep(uint64_t rdi, uint64_t rsi);

static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) {
	switch (exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
		case INVALID_OPCODE_ID:
			invalid_opcode();
	}
}

static void zero_division() {
	// TODO
	vdClearScreen();
	vdPrint("Arithmetic exception: division by zero\n",0x00FFFFFF);
	nanosleep(2,0);
	vdPrint("Press any key to recover...\n",0x00FFFFFF);

	while(1) _hlt();	// Loops infinitely at least for now.
	// imrpimir registros en pantalla
	// volver a la shell (hacer una funcion que me ejecute la shell de vuelta asi la llamo)
}

static void invalid_opcode(){
	vdClearScreen();
	vdPrint("Invalid Opcode exception: command not recognised\n",0x00FFFFFF);
	nanosleep(2,0);
	vdPrint("Press any key to recover...\n",0x00FFFFFF);

}