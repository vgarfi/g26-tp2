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
    syshideCursor();
    print("\nLoading eliminator...");
    syssleep(2,0);
    eliminatorGame();
}

void clear (void) {
    sysclearScreen();
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
    regAux = sysprintRegs();
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

    syshideCursor();
    sysprintCursor();

    sysbeepSound(4, DO);
	sysbeepSound(4, DO_SOST);
	sysbeepSound(4, SOL);
	sysbeepSound(4, MI);
	sysbeepSound(4, SOL);
	sysbeepSound(4, MI);
	
	sysbeepSound(4, DO_SOST);
	sysbeepSound(4, DO);
	sysbeepSound(4, SOL_SOST);
	sysbeepSound(4, FA);
	sysbeepSound(4, SOL_SOST);
	sysbeepSound(4, FA);

	sysbeepSound(4, DO);
	sysbeepSound(4, DO_SOST);
	sysbeepSound(4, SOL);
	sysbeepSound(4, MI);
	sysbeepSound(4, SOL);
	sysbeepSound(4, MI);

	sysbeepSound(2, FA);
	sysbeepSound(3, FA_SOST);
	sysbeepSound(2, SOL);
	sysbeepSound(3, SOL_SOST);
	sysbeepSound(2, LA);
	sysbeepSound(3, SI);
	sysbeepSound(2, DO_PRIMA);

    sysshowCursor();
    sysprintCursor();
}