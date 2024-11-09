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
#include "include/ipc.h"
#include "include/phylo.h"

char* dateTimeAux;
int zoomAux, regAux;

char* interactive_modes[]  = {
    "testp", "testprio", "testmem", "testsync", "loop", "cat", "wc", "filter", "phylo"
};

int (*mode_functions[])(int) = {
    process_test,
    priorities_test,
    memory_test,
    sync_test,
    loop,
    cat,
    wc, 
    filter,
    phylosophers
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

int process_test(TScope scope) {
  return sysCreateProcess(TEST_PROCESSES, 2, test_args_proc, (int64_t (*)(int, char**))test_processes, scope);
}

static char * test_args_prio[] = {TEST_PRIORITY, 0};

int priorities_test(TScope scope){
    return sysCreateProcess(TEST_PRIORITY, 1, test_args_prio, (int64_t (*)(int, char**))test_priorities, scope);
}

int ps_printing(void){
    sysPs();
}

int mem(void){
    sysMem();
}

static char * test_args_memory[] = {TEST_MEMORY, "1024", 0};

int memory_test(TScope scope){
    return sysCreateProcess(TEST_MEMORY, 2, test_args_memory, (int64_t (*)(int, char**))test_mm, scope);
}

static char * test_sync_args[] = {TEST_SYNC, 0};
int sync_test(TScope scope){
    return sysCreateProcess(TEST_SYNC, 1, test_sync_args, (int64_t (*)(int, char**))initialize_sync_testing, scope);
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

int loop(TScope scope) {
    return sysCreateProcess(LOOP, 1, loop_args, loop_process, scope);
}

int (*get_interactive_mode(const char* mode))(int) {
    for (int i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        if (strcasecmp(mode, interactive_modes[i]) == SELECTED_MODE) {
            return mode_functions[i];
        }
    }
    return 0;
}
void niky(){

}
void pipe_processes(char* input) {
    char p1[15], p2[15];
    strsplit(input, '|', p1, p2);
    strtrim(p1);
    strtrim(p2);
    int(*process_one)(int) = get_interactive_mode(p1);
    int(*process_two)(int) = get_interactive_mode(p2);

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
    char pipe_name; // Anonymous pipe
    if (sysCreatePipe(pipe_fds, pipe_name) == -1) {
        printf("\nError creando pipes entre procesos",0,0,0);
        return;
    }
    niky();
    int p1Pid = process_one(FOREGROUND);
    int p2Pid = process_two(FOREGROUND);
    sysSetWriteFileDescriptor(p1Pid, pipe_fds[1]);
    sysSetReadFileDescriptor(p2Pid, pipe_fds[0]);
    sysWaitPid(p1Pid);
}

void create_background_process(char* input) {
    char p1[15], p2[1];
    strsplit(input, '&', p1, p2);
    strtrim(p1);
    int(*process)() = get_interactive_mode(p1);
    process(BACKGROUND);
}

// ! Hacer una lista de procesos
int cat(TScope scope) {
    return sysCreateProcess(CAT, 1, cat_args, cat_process, scope);
}

int wc(TScope scope) {
    return sysCreateProcess(WC, 1, wc_args, wc_process, scope);
}

int filter(TScope scope) {
    return sysCreateProcess(FILTER, 1, filter_args, filter_process, scope);
}

static char * phylos_args[] = {PHYLOS, 0};
int phylosophers(TScope scope) {
    return sysCreateProcess(PHYLOS, 1, phylos_args, phylos, scope);
}