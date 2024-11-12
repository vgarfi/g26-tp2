// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <interactiveModes.h>
#include <string.h>

int (*interactiveFunctions[])(int) = {
    processTest,
    prioritiesTest,
    memoryTest,
    syncTest,
    loop,
    cat,
    wc,
    filter,
    phylosophers
};

int (*getInteractiveMode(const char* mode))(int) {
    for (int i = 0; i < sizeof(interactiveModes) / sizeof(interactiveModes[0]); i++) {
        if (strcasecmp(mode, interactiveModes[i]) == SELECTED_MODE) {
            return interactiveFunctions[i];
        }
    }
    return 0;
}

void pipeProcesses(char* input) {
    char p1[15], p2[15];
    strsplit(input, '|', p1, p2);
    strtrim(p1);
    strtrim(p2);
    int(*processOne)(int) = getInteractiveMode(p1);
    int(*processTwo)(int) = getInteractiveMode(p2);

    if (processOne == 0 || processTwo == 0) {
        printColor("\nERROR: ", 0x00FF0000);
        print("'");
        print(processOne == 0? p1 : p2);        
        print("' is not a pipeable mode\n");
        return;
    }

    int pipeFds[2];
    char* pipeName; // Anonymous pipe
    pipeName = 00;
    if (sysCreatePipe(pipeFds, pipeName) == -1) {
        print("\nError creating pipe between processes");
        return;
    }
    int p1Pid = processOne(FOREGROUND);
    int p2Pid = processTwo(FOREGROUND);
    sysSetWriteFileDescriptor(p1Pid, pipeFds[1]);
    sysSetReadFileDescriptor(p2Pid, pipeFds[0]);
    sysWaitPid(p1Pid);
}

void createBackgroundProcess(char* input) {
    char p1[15], p2[1];
    strsplit(input, '&', p1, p2);
    strtrim(p1);
    int(*process)() = getInteractiveMode(p1);
    if (process == 0){
        printColor("\nERROR: ", 0x00FF0000);
        print("'");
        print(p1);        
        print("' does not allow to run in background\n");
        return;
    }
    process(BACKGROUND);
}