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

void process_test(int* fds);
void priorities_test(int* fds);
void memory_test(int* fds);
void sync_test(int* fds);
void ps_printing(void);
void killp();
void blockp();
void unblockp();

void loop();

void pipe_processes(char* input);

#endif
