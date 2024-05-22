
#define ZERO_EXCEPTION_ID 0
#include <naiveConsole.h>

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	// TODO
	ncPrint("Arithmetic exception: division by zero");
	// imrpimir registros en pantalla
	// volver a la shell (hacer una funcion que me ejecute la shell de vuelta asi la llamo)
}