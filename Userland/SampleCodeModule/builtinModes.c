// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <builtinModes.h>
#include <string.h>


void (*builtinFunctions[])(void) = {
    help,
    playEasterEgg,
    zoomin,
    zoomout,
    time,
    date,
    clear,
    registers,
    psPrinting,
    mem,
    blockp,
    unblockp,
    nicep,
    killp
};

void playEasterEgg() {
    printColor("I'm", RED);
    printColor(" an", YELLOW);
    printColor(" eas", GREEN);
    printColor("ter ", BLUE);
    printColor("egg", WHITE);
    printColor("!\n", YELLOW);

    sysHideCursor();
    sysPrintCursor();

    sysBeepSound(2, DO);
	sysBeepSound(2, DO_SOST);
	sysBeepSound(2, SOL);
	sysBeepSound(2, MI);
	sysBeepSound(2, SOL);
	sysBeepSound(2, MI);
	
	sysBeepSound(2, DO_SOST);
	sysBeepSound(2, DO);
	sysBeepSound(2, SOL_SOST);
	sysBeepSound(2, FA);
	sysBeepSound(2, SOL_SOST);
	sysBeepSound(2, FA);

	sysBeepSound(2, DO);
	sysBeepSound(2, DO_SOST);
	sysBeepSound(2, SOL);
	sysBeepSound(2, MI);
	sysBeepSound(2, SOL);
	sysBeepSound(2, MI);

	sysBeepSound(1, FA);
	sysBeepSound(1, FA_SOST);
	sysBeepSound(1, SOL);
	sysBeepSound(1, SOL_SOST);
	sysBeepSound(1, LA);
	sysBeepSound(1, SI);
	sysBeepSound(1, DO_PRIMA);

    sysShowCursor();
    sysPrintCursor();
}

void notFound(char* commandNotFound){
    print(commandNotFound); 
    print(": command not found.\n");
}

void registers()  {
    int regAux = sysPrintRegs();
    if(regAux){
        print("You need to save registers first by pressing ALT\n");
    }
}

void zoomout() {
    int zoomAux = decTextSize();
    if(zoomAux){
        print("Minimum size reached.\n");
    }
}

void zoomin() {
    int zoomAux = incTextSize();
    if(zoomAux){
        print("Maximum size reached.\n");
    }
}


void help (void) {
    for(int i=0; strcasecmp(helpText[i], "end")!=0; i++){
        printColor(helpText[i], YELLOW);
    }
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

void psPrinting(void){
    sysPs();
}

void mem(void) {
    sysMem();
}


void killp(void) {
    printf("\nEnter PID of process to ", 0,0,0);
    printColor("KILL", 0x00FF0000);
    printf(": ", 0,0,0);
    char option[5];
    scanf(option, 5);
    int pid = atoi(option);
    printColor("\nKILLING ", 0x00FF0000);
    printf("process with PID: %d (if exists)\n", pid,0,0);
    sysKillProcess((uint8_t)pid);
}

void unblockp(void) {
    printf("\nEnter PID of process to ", 0,0,0);
    printColor("UNBLOCK", 0x00FFE47B);
    printf(": ", 0,0,0);
    char option[5];
    scanf(option, 5);
    int pid = atoi(option);
    printColor("\nUNBLOCKING ", 0x00FFE47B);
    printf("process with PID: %d (if exists)\n", pid,0,0);
    sysUnblockProcess((uint8_t)pid);
}

void nicep(void) {
    printf("\nEnter PID of process to ", 0,0,0);
    printColor("CHANGE PRIORITY", 0x00146DFA);
    printf(": ", 0,0,0);
    char option[5];
    scanf(option, 5);
    int pid = atoi(option);
    printf("Now enter the ", 0,0,0);
    printColor("new", 0x00146DFA);
    printf(" priority: ", 0,0,0);;
    char option2[5];
    scanf(option2, 5);
    int newPriority = atoi(option2);
    if (newPriority < 1) {
        return;
    }
    sysNice((uint8_t)pid, (uint8_t)newPriority);
}

void blockp(void) {
    printf("\nEnter PID of process to ", 0,0,0);
    printColor("BLOCK", 0x00C72C29);
    printf(": ", 0,0,0);
    char option[5];
    scanf(option, 5);
    int pid = atoi(option);
    printColor("\nBLOCKING ", 0x00C72C29);
    printf("process with PID: %d (if exists)\n", pid,0,0);
    sysBlockProcess((uint8_t)pid);
}