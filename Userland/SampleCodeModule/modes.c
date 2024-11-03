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


char* dateTimeAux;
int zoomAux, regAux;

char* pipeable_modes[]  = {
    "testp", "testprio", "ps", "testmem", "testsync", "loop"
};

void (*mode_functions[])(int*) = {
    process_test,
    priorities_test,
    ps_printing,
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

void process_test(int* fds) {
  sysCreateProcess(TEST_PROCESSES, 2, test_args_proc, (int64_t (*)(int, char**))test_processes, fds);
}

static char * test_args_prio[] = {TEST_PRIORITY, 0};

void priorities_test(int* fds){
    sysCreateProcess(TEST_PRIORITY, 1, test_args_prio, (int64_t (*)(int, char**))test_priorities, fds);
}

void ps_printing(){
    sysPs();
}

static char * test_args_memory[] = {TEST_MEMORY, "1024", 0};

void memory_test(int* fds){
    sysCreateProcess(TEST_MEMORY, 2, test_args_memory, (int64_t (*)(int, char**))test_mm, fds);
}

static char * sync_args_memory_sem[] = {TEST_SYNC, "5", "1", 0};
static char * sync_args_memory_not_sem[] = {TEST_SYNC, "5", "0", 0};


void sync_test(int* fds){
    printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
    char option[5];
    scanf(option, 5);
    while (strcasecmp(option, "y") != 0 && strcasecmp(option, "n") != 0) {
        printColor("ERROR: ",0x00FF0000);
        printf(option,0,0,0);
        printf(" is not a valid option",0,0,0);
        printf("\nWould you like to use semaphores for testing? [Y/N]: ",0,0,0);
        scanf(option, 5);
    }
    
    printf("\nYou decided ",0,0,0);
    if (strcasecmp(option, "n") == 0) printf("not ",0,0,0);
    printf("to use semaphores. Starting tests...\n",0,0,0);

    int testPid;

    if (strcasecmp(option, "n") == 0) {
        testPid = sysCreateProcess(TEST_SYNC, 3, sync_args_memory_not_sem,  (int64_t (*)(int, char**))test_sync, fds);
    } else {
        testPid = sysCreateProcess(TEST_SYNC, 3, sync_args_memory_sem,  (int64_t (*)(int, char**))test_sync, fds);
    }
    sysNice(testPid, 5);
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

void loop(int* fds){
    sysLoop(fds);
}

void (*get_pipeable_mode(const char* mode))(int*) {
    for (int i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        if (strcasecmp(mode, pipeable_modes[i]) == SELECTED_MODE) {
            return mode_functions[i];
        }
    }
    return 0;
}

void pipe_processes(char* input) {
    char p1[15], p2[15];
    strsplit(input, '!', p1, p2);
    strtrim(p1);
    strtrim(p2);
    void(*process_one)(int*) = get_pipeable_mode(p1);
    void(*process_two)(int*) = get_pipeable_mode(p2);

    if (process_one == 0 || process_two == 0) {
        // TODO claramente mejorar los mensajes de error
        if (process_one == 0) {
            printf("\nERROR: ", 0,0,0);
            printf(p1, 0,0,0);
            printf("no es un proceso pipeable", 0,0,0);
        }
        else {
            printf("\nERROR: ", 0,0,0);
            printf(p2, 0,0,0);
            printf("no es un proceso pipeable", 0,0,0);
        }
        return;
    }

    int pipe_fds[2];
    char pipe_name[32];
    strconcat(pipe_name, p1, "-");
    strconcat(pipe_name, pipe_name, p2);
    sysCreatePipe(pipe_name, pipe_fds);
    
    int p1_fds[2], p2_fds[2];
    p1_fds[0] = STDIN;
    p1_fds[1] = pipe_fds[0];
    p2_fds[0] = pipe_fds[1];
    p2_fds[1] = STDOUT;
    
    printf("p1_fds: [%d, %d]\n", p1_fds[0], p1_fds[1], 0);
    printf("p2_fds: [%d, %d]\n", p2_fds[0], p2_fds[1], 0);
    
    process_one(p1_fds);
    process_two(p2_fds);
}

