#include "include/shell.h"
#include "include/modes.h"
#include "include/colors.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/string.h"

int init(){
    printColor("Welcome to Shell! Type HELP for command information.\n\n", YELLOW);
    char commandPrompt[32] = {0};
    char buffer[10];
    while(IDLE_MODE) {
        sysClearKbEntry();
        printColor("$", GREEN);
        print("> ");
        sysShowCursor();
        scanf(commandPrompt, 32);
        if(strcasecmp(commandPrompt, modes[HELP_MODE]) == SELECTED_MODE) help();
        else if(strcasecmp(commandPrompt, modes[ELIMINATOR_MODE]) == SELECTED_MODE) sysWaitPid(playEliminator());
        else if(strcasecmp(commandPrompt, modes[CLEAR_MODE]) == SELECTED_MODE) clear();
        else if(strcasecmp(commandPrompt, modes[TIME_MODE]) == SELECTED_MODE) time();
        else if(strcasecmp(commandPrompt, modes[DATE_MODE]) == SELECTED_MODE) date();
        else if(strcasecmp(commandPrompt, modes[EASTEREGG_MODE]) == SELECTED_MODE) playEasterEgg();
        else if(strcasecmp(commandPrompt, modes[ZOOMIN_MODE]) == SELECTED_MODE ) zoomin();
        else if(strcasecmp(commandPrompt, modes[ZOOMOUT_MODE]) == SELECTED_MODE) zoomout();
        else if(strcasecmp(commandPrompt, modes[DIVBYZERO_MODE]) == SELECTED_MODE) divByZero();
        else if(strcasecmp(commandPrompt, modes[INVALIDOPCODE_MODE]) == SELECTED_MODE) invalidOp();
        else if(strcasecmp(commandPrompt, modes[REGISTERS_MODE]) == SELECTED_MODE) registers();
        else if(strcasecmp(commandPrompt, modes[TESTP_MODE]) == SELECTED_MODE) sysWaitPid(processTest(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[TESTPRIO_MODE]) == SELECTED_MODE) sysWaitPid(prioritiesTest(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[PS_MODE]) == SELECTED_MODE) psPrinting();
        else if(strcasecmp(commandPrompt, modes[TESTMEM_MODE]) == SELECTED_MODE) sysWaitPid(memoryTest(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[TEST_SYNC_MODE]) == SELECTED_MODE) sysWaitPid(syncTest(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[BLOCKP_MODE]) == SELECTED_MODE) blockp();
        else if(strcasecmp(commandPrompt, modes[UNBLOCKP_MODE]) == SELECTED_MODE) unblockp();
        else if(strcasecmp(commandPrompt, modes[KILLP_MODE]) == SELECTED_MODE) killp();
        else if(strcasecmp(commandPrompt, modes[LOOP_MODE]) == SELECTED_MODE) sysWaitPid(loop(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[CAT_MODE]) == SELECTED_MODE) sysWaitPid(cat(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[WC_MODE]) == SELECTED_MODE) sysWaitPid(wc(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[FILTER_MODE]) == SELECTED_MODE) sysWaitPid(filter(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[PHYLOS]) == SELECTED_MODE) sysWaitPid(phylosophers(FOREGROUND));
        else if(strcasecmp(commandPrompt, modes[MEM]) == SELECTED_MODE) mem();
        else if(contains(commandPrompt, '|')) pipeProcesses(commandPrompt);
        else if(contains(commandPrompt, '&')) createBackgroundProcess(commandPrompt);
        else notFound(commandPrompt);
    }
}