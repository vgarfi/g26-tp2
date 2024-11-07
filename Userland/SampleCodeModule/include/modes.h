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

int process_test(TScope scope);
int priorities_test(TScope scope);
int memory_test(TScope scope);
int sync_test(TScope scope);
int ps_printing();
void killp();
void blockp();
void unblockp();

int loop(TScope scope);
void pipe_processes(char* input);
void create_background_process(char* input);

int cat(TScope scope);
int wc(TScope scope);
int filter(TScope scope);

int phylosophers(TScope scope);

#endif
