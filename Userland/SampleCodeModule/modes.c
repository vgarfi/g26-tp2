#include "include/modes.h"
#include "include/shell.h"
#include "include/eliminatorGame.h"
#include "include/stdio.h"
#include "include/string.h"
#include "include/syscalls.h"
#include "include/lib.h"
#include "include/exceptions.h"
#include "include/dateTime.h"
#include "include/colors.h"
#include "include/utils.h"

char* dateTimeAux;
int zoomAux, regAux;


void help (void) {
    for(int i=0; strcasecmp(helpText[i], "end")!=0; i++){
        printColor(helpText[i], YELLOW);
    }
}

void eliminator() {
    sysHideCursor();
    print("\nLoading eliminator...");
    sysSleep(2000);
    eliminatorGame();
}

void clear (void) {
    sysClearScreen();
}

void time(void) {
    printTime();
}

void date(void) {
    printDate();
}

void zoomin() {
    zoomAux = incTextSize();
    if(zoomAux)
        print("Maximum size reached.\n");
}

void zoomout() {
    zoomAux = decTextSize();
    if(zoomAux)
        print("Minimum size reached.\n");
}

void divByZero() {
    divZero();
}

void invalidOp(){
    invalidOpcode();
}

void registers()  {
    regAux = sysPrintRegs();
    if(regAux){
        print("You need to save registers first by pressing ALT\n");
    }
}

void notFound(char* commandNotFound){
    print(commandNotFound); 
    print(": command not found.\n");
}

void playEasterEgg(){
    printColor("I'm", RED);
    printColor(" an", YELLOW);
    printColor(" eas", GREEN);
    printColor("ter ", BLUE);
    printColor("egg", WHITE);
    printColor("!\n", YELLOW);

    sysHideCursor();
    sysPrintCursor();

    sysBeepSound(4, DO);
	sysBeepSound(4, DO_SOST);
	sysBeepSound(4, SOL);
	sysBeepSound(4, MI);
	sysBeepSound(4, SOL);
	sysBeepSound(4, MI);
	
	sysBeepSound(4, DO_SOST);
	sysBeepSound(4, DO);
	sysBeepSound(4, SOL_SOST);
	sysBeepSound(4, FA);
	sysBeepSound(4, SOL_SOST);
	sysBeepSound(4, FA);

	sysBeepSound(4, DO);
	sysBeepSound(4, DO_SOST);
	sysBeepSound(4, SOL);
	sysBeepSound(4, MI);
	sysBeepSound(4, SOL);
	sysBeepSound(4, MI);

	sysBeepSound(2, FA);
	sysBeepSound(3, FA_SOST);
	sysBeepSound(2, SOL);
	sysBeepSound(3, SOL_SOST);
	sysBeepSound(2, LA);
	sysBeepSound(3, SI);
	sysBeepSound(2, DO_PRIMA);

    sysShowCursor();
    sysPrintCursor();
}