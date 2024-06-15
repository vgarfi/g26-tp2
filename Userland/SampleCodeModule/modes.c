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
#include "include/piano.h"
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

void pianoMode(){
    piano();
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

    sysBeepSound(200, C);
	sysBeepSound(200, Db);
	sysBeepSound(200, G);
	sysBeepSound(200, E);
	sysBeepSound(200, G);
	sysBeepSound(200, E);
	
	sysBeepSound(200, Db);
	sysBeepSound(200, C);
	sysBeepSound(200, Ab);
	sysBeepSound(200, F);
	sysBeepSound(200, Ab);
	sysBeepSound(200, F);

	sysBeepSound(200, C);
	sysBeepSound(200, Db);
	sysBeepSound(200, G);
	sysBeepSound(200, E);
	sysBeepSound(200, G);
	sysBeepSound(200, E);

	sysBeepSound(100, F);
	sysBeepSound(150, Gb);
	sysBeepSound(100, G);
	sysBeepSound(150, Ab);
	sysBeepSound(100, A);
	sysBeepSound(150, B);
	sysBeepSound(100, C5);

    sysShowCursor();
    sysPrintCursor();
}