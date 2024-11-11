// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <shell.h>
#include <interactiveModes.h>
#include <colors.h>
#include <syscalls.h>
#include <stdio.h>
#include <string.h>
#include <builtinModes.h>
#include <processModes.h>

extern int (*processFunctions[])(int);
extern void (*builtinFunctions[])(void);

int init(){
    printColor("Welcome to Shell! Type HELP for command information.\n\n", YELLOW);
    char commandPrompt[32] = {0};
    while(SHELL_MODE) {
        char found = 0;
        sysClearKbEntry();
        printColor("$", GREEN);
        print("> ");
        sysShowCursor();
        scanf(commandPrompt, 32);
        for(int b = 0; !found && b < sizeof(builtinModes) / sizeof(builtinModes[0]); b++) {
            if (strcasecmp(commandPrompt, builtinModes[b]) == SELECTED_MODE) {
                builtinFunctions[b]();
                found = 1;
            }
        }
        for(int p = 0; !found && p < sizeof(processModes) / sizeof(processModes[0]); p++) {
            if (strcasecmp(commandPrompt, processModes[p]) == SELECTED_MODE) {
                found = 1;
                sysWaitPid(processFunctions[p](FOREGROUND));
            }
        }
        if (!found) {
            if (contains(commandPrompt, '|')) {
                pipeProcesses(commandPrompt);
                found = 1;
            } else if (contains(commandPrompt, '&')) {
                createBackgroundProcess(commandPrompt);
                found = 1;
            } else {
                notFound(commandPrompt);
            }
        }
    }
}