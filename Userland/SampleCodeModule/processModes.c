#include "include/processModes.h"

char * eliminator_args[] = {ELIMINATOR_PROCESS, 0};
char * test_args_proc[] = {TEST_PROCESSES, "5", 0};
char * test_args_prio[] = {TEST_PRIORITY, 0};
char * test_args_memory[] = {TEST_MEMORY, "1024", 0};
char * test_sync_args[] = {TEST_SYNC, 0};
char * loop_args[] = {LOOP, 0};
char * cat_args[] = {CAT, 0};
char * wc_args[] = {WC, 0};
char * filter_args[] = {FILTER, 0};
char * phylos_args[] = {PHYLOS, 0};

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
    return sysCreateProcess(CAT, 1, cat_args, catProcess, scope);
}

int wc(TScope scope) {
    return sysCreateProcess(WC, 1, wc_args, wcProcess, scope);
}

int filter(TScope scope) {
    return sysCreateProcess(FILTER, 1, filter_args, filterProcess, scope);
}

int phylosophers(TScope scope) {
    return sysCreateProcess(PHYLOS, 1, phylos_args, phylos, scope);
}

int playEliminator(TScope scope) {
    sysHideCursor();
    print("\nLoading eliminator...");
    sysSleep(2,0);
    return sysCreateProcess(ELIMINATOR_PROCESS, 1, eliminator_args, (int64_t (*)(int, char**))eliminatorGame, FOREGROUND);
}

int processTest(TScope scope) {
  return sysCreateProcess(TEST_PROCESSES, 2, test_args_proc, (int64_t (*)(int, char**))testProcesses, scope);
}

int prioritiesTest(TScope scope){
    return sysCreateProcess(TEST_PRIORITY, 1, test_args_prio, (int64_t (*)(int, char**))testPriorities, scope);
}

int memoryTest(TScope scope){
    return sysCreateProcess(TEST_MEMORY, 2, test_args_memory, (int64_t (*)(int, char**))testMm, scope);
}

int syncTest(TScope scope){
    return sysCreateProcess(TEST_SYNC, 1, test_sync_args, (int64_t (*)(int, char**))initialize_syncTesting, scope);
}

int loop(TScope scope) {
    return sysCreateProcess(LOOP, 1, loop_args, loopProcess, scope);
}