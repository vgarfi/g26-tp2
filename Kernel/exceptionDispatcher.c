#define ZERO_EXCEPTION_ID 0
#include <naiveConsole.h>
#include <videoDriver.h>
#include <keyboard.h>
#include <interrupts.h>
static void zero_division();

void exceptionDispatcher(int exception) {
	switch (exception)
		case ZERO_EXCEPTION_ID:
			zero_division();
		return;
}

static void zero_division() {
	// TODO
	vdClearScreen();
	vdPrint("Arithmetic exception: division by zero\n",0x00FFFFFF);
	vdPrint("Press any key to recover\n",0x00FFFFFF);
	//ncPrint("Arithmetic exception: division by zero");
	// imrpimir registros en pantalla
	// volver a la shell (hacer una funcion que me ejecute la shell de vuelta asi la llamo)
}