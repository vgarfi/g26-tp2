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
#include "include/test_proc.h"
#include "include/test_mm.h"
#include "include/test_sync.h"
#include "include/loop.h"

char* dateTimeAux;
int zoomAux, regAux;

char* pipeable_modes[]  = {
    "testp", "testprio", "testmem", "testsync", "loop"
};

int (*mode_functions[])() = {
    process_test,
    priorities_test,
    memory_test,
    sync_test,
    loop
};

void help (void) {
    for(int i=0; strcasecmp(helpText[i], "end")!=0; i++){
        printColor(helpText[i], YELLOW);
    }
}

void eliminator() {
    sysHideCursor();
    print("\nLoading eliminator...");
    sysSleep(2,0);
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

    sysBeepSound(220, DO);
	sysBeepSound(220, DO_SOST);
	sysBeepSound(220, SOL);
	sysBeepSound(220, MI);
	sysBeepSound(220, SOL);
	sysBeepSound(220, MI);
	
	sysBeepSound(220, DO_SOST);
	sysBeepSound(220, DO);
	sysBeepSound(220, SOL_SOST);
	sysBeepSound(220, FA);
	sysBeepSound(220, SOL_SOST);
	sysBeepSound(220, FA);

	sysBeepSound(220, DO);
	sysBeepSound(220, DO_SOST);
	sysBeepSound(220, SOL);
	sysBeepSound(220, MI);
	sysBeepSound(220, SOL);
	sysBeepSound(220, MI);

	sysBeepSound(110, FA);
	sysBeepSound(165, FA_SOST);
	sysBeepSound(110, SOL);
	sysBeepSound(165, SOL_SOST);
	sysBeepSound(110, LA);
	sysBeepSound(165, SI);
	sysBeepSound(110, DO_PRIMA);

    sysShowCursor();
    sysPrintCursor();
}

static char * test_args_proc[] = {TEST_PROCESSES, "5", 0};

int process_test() {
  return sysCreateProcess(TEST_PROCESSES, 2, test_args_proc, (int64_t (*)(int, char**))test_processes);
}

static char * test_args_prio[] = {TEST_PRIORITY, 0};

int priorities_test(){
    return sysCreateProcess(TEST_PRIORITY, 1, test_args_prio, (int64_t (*)(int, char**))test_priorities);
}

void ps_printing(){
    sysPs();
}

static char * test_args_memory[] = {TEST_MEMORY, "1024", 0};

int memory_test(){
    return sysCreateProcess(TEST_MEMORY, 2, test_args_memory, (int64_t (*)(int, char**))test_mm);
}

static char * test_sync_args[] = {TEST_SYNC, 0};
int sync_test(){
    return sysCreateProcess(TEST_SYNC, 1, test_sync_args, (int64_t (*)(int, char**))initialize_sync_testing);
}

void killp(){
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

void unblockp(){
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

void blockp(){
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

void basic_sleep(){
    for (int i = 0; i < 20000000; i++);
}


int64_t loop_process(int argc, char** argv) {
    // printf("\n",0,0,0);
    while(1) {
        basic_sleep();
        printf("Hello (from ", 0,0,0);
        printColor("LOOP", 0x0000D4C1);
        printf(") with PID: %d ", sysGetCurrentPid(),0,0);
        printf("\n",0,0,0);
    }
}

static char * loop_args[] = {LOOP, 0};
int loop() {
    return sysCreateProcess(LOOP, 1, loop_args, loop_process);
}

int (*get_pipeable_mode(const char* mode))(void) {
    for (int i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        if (strcasecmp(mode, pipeable_modes[i]) == SELECTED_MODE) {
            return mode_functions[i];
        }
    }
    return 0;
}

static char * dummy_args[] = {"dummy", 0};
int64_t dummy_process(int argc, char** argv) {
    char buf[256];
    while(1) {
        scanf(buf, 256);
        print("\nLeido desde el pipe: ");
        print(buf);
    }
}

void pipe_processes(char* input) {
    char p1[15], p2[15];
    strsplit(input, '|', p1, p2);
    strtrim(p1);
    strtrim(p2);
    int(*process_one)() = get_pipeable_mode(p1);
    int(*process_two)() = get_pipeable_mode(p2);

    if (process_one == 0 || process_two == 0) {
        // TODO claramente mejorar los mensajes de error
        if (process_one == 0) {
            printf("\nERROR: '", 0,0,0);
            printf(p1, 0,0,0);
            printf("' no es un proceso pipeable", 0,0,0);
        }
        else {
            printf("\nERROR: '", 0,0,0);
            printf(p2, 0,0,0);
            printf("' no es un proceso pipeable", 0,0,0);
        }
        return;
    }

    int pipe_fds[2];
    char pipe_name[32];
    strconcat(pipe_name, p1, "-");
    strconcat(pipe_name, pipe_name, p2);
    
    
    if (sysCreatePipe(pipe_name, pipe_fds) == -1) {
        printf("\nError creando pipes entre procesos",0,0,0);
        return;
    }
    
    int p1Pid = process_one();
    int p2Pid = process_two();
    // int p2Pid = sysCreateProcess("dummy", 1, dummy_args, dummy_process);
    sysSetWriteFileDescriptor(p1Pid, pipe_fds[1]);
    sysSetReadFileDescriptor(p2Pid, pipe_fds[0]);
}

