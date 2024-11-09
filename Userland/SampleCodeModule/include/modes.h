#ifndef MODES_H
#define MODES_H

#include <utils.h>

void help(void);
void divByZero(void);
void invalidOp(void);
void zoomin(void);
void zoomout(void);
void time(void);
void date(void);
void clear(void);
void registers(void);
void eliminator(void);
void notFound(char* commandNotFound);
void playEasterEgg();

int processTest(TScope scope);
int prioritiesTest(TScope scope);
int memoryTest(TScope scope);
int syncTest(TScope scope);
int psPrinting(void);
int mem(void);
void killp(void);
void blockp(void);
void unblockp(void);

int loop(TScope scope);
void pipeProcesses(char* input);
void createBackgroundProcess(char* input);

int cat(TScope scope);
int wc(TScope scope);
int filter(TScope scope);

int phylosophers(TScope scope);

#endif
