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

int (*get_interactive_mode(const char* mode))(int) {
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
    char* pipe_name; // Anonymous pipe
    pipe_name = 00;
    if (sysCreatePipe(pipe_fds, pipe_name) == -1) {
        printf("\nError creando pipes entre procesos",0,0,0);
        return;
    }
    int p1Pid = process_one(FOREGROUND);
    int p2Pid = process_two(FOREGROUND);
    sysSetWriteFileDescriptor(p1Pid, pipe_fds[1]);
    sysSetReadFileDescriptor(p2Pid, pipe_fds[0]);
    sysWaitPid(p1Pid);
}

void createBackgroundProcess(char* input) {
    char p1[15], p2[1];
    strsplit(input, '&', p1, p2);
    strtrim(p1);
    int(*process)() = get_interactive_mode(p1);
    process(BACKGROUND);
}