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

char* dateTimeAux;
int zoomAux, regAux;


void help (void) {
    for(int i = 0; i < HELP_TEXTS; i++){
        printColor(helpText[i], YELLOW);
    }
}

void eliminator() {
    print("\nLoading eliminator...");
    sleep(2,0);
    hideCursor();
    eliminatorGame();
}

void clear (void) {
    clearScreen();
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
    invalidOp();
}

void registers()  {
    regAux = printRegs();
    if(regAux){
        print("You need to save registers first by pressing ALT\n");
    }
}

void notFound(char* commandNotFound){
    print(commandNotFound); 
    print(": command not found.\n");
}