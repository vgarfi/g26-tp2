#ifndef MODES_H
#define MODES_H

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

int process_test();
int priorities_test();
int memory_test();
int sync_test();
void ps_printing(void);
void killp();
void blockp();
void unblockp();

int loop();
void pipe_processes(char* input);

#endif
