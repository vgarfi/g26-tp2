// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <processModes.h>

char * eliminatorArgs[] = {ELIMINATOR_PROCESS, 0};
char * testArgsProc[] = {TEST_PROCESSES, "5", 0};
char * testArgsPrio[] = {TEST_PRIORITY, 0};
char * testArgsMemory[] = {TEST_MEMORY, "1024", 0};
char * testArgsSync[] = {TEST_SYNC, 0};
char * loopArgs[] = {LOOP, 0};
char * catArgs[] = {CAT, 0};
char * wcArgs[] = {WC, 0};
char * filterArgs[] = {FILTER, 0};
char * phylosArgs[] = {PHYLOS, 0};

int (*processFunctions[])(int) = {
    playEliminator,
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

int cat(TScope scope) {
    return sysCreateProcess(CAT, 1, catArgs, catProcess, scope);
}

int wc(TScope scope) {
    return sysCreateProcess(WC, 1, wcArgs, wcProcess, scope);
}

int filter(TScope scope) {
    return sysCreateProcess(FILTER, 1, filterArgs, filterProcess, scope);
}

int phylosophers(TScope scope) {
    return sysCreateProcess(PHYLOS, 1, phylosArgs, phylos, scope);
}

int playEliminator(TScope scope) {
    sysHideCursor();
    print("\nLoading eliminator...");
    sysSleep(2,0);
    int eliminatorPid = sysCreateProcess(ELIMINATOR_PROCESS, 1, eliminatorArgs, (int64_t (*)(int, char**))eliminatorGame, FOREGROUND);
    sysNice(eliminatorPid, 20);
    return eliminatorPid;

}

int processTest(TScope scope) {
  return sysCreateProcess(TEST_PROCESSES, 2, testArgsProc, (int64_t (*)(int, char**))testProcesses, scope);
}

int prioritiesTest(TScope scope){
    return sysCreateProcess(TEST_PRIORITY, 1, testArgsPrio, (int64_t (*)(int, char**))testPriorities, scope);
}

int memoryTest(TScope scope){
    return sysCreateProcess(TEST_MEMORY, 2, testArgsMemory, (int64_t (*)(int, char**))testMm, scope);
}

int syncTest(TScope scope){
    return sysCreateProcess(TEST_SYNC, 1, testArgsSync, (int64_t (*)(int, char**))initializeSyncTesting, scope);
}

int loop(TScope scope) {
    return sysCreateProcess(LOOP, 1, loopArgs, loopProcess, scope);
}