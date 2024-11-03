#ifndef __SYSCALLHANDLE_H_
#define __SYSCALLHANDLE_H_

#include <stdint.h>

int setCursor(uint64_t x, uint64_t y);
int hideCursor();
int showCursor();
int printCursor();

int upArrowValue();
int leftArrowValue();
int downArrowValue();
int rightArrowValue();

int printRect(int x,int y,int base,int height,uint32_t hexColor);
int printSquare (int x, int y,int side, uint32_t hexColor);

int clearScreen();
int msSleep(uint64_t secs, uint64_t ticks);     // rdi : ms
int printRegs(void);

int sound(uint64_t ms, uint64_t freq);

int getCurrentSeconds(void);
int getCurrentMinutes(void);
int getCurrentHours(void);

int getCurrentDay(void);
int getCurrentMonth(void);
int getCurrentYear(void);

int incSize();
int decSize();
int getZoomLevel();
int setZoomLevel(int zoomLevel);

int read(uint64_t fd, char * buf, uint64_t count);
int write(uint64_t fd, char * buf, uint64_t count, uint64_t hexColor);

int cleanKbBuffer(void);
int isctrlPressed(void);

int getCurrentPid(void);
int exitProcess(void);
int createProcess(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), int* fds);
int blockProcess(uint8_t pid);
int unblockProcess(uint8_t pid);
int killProcess(uint8_t pid);
int nice(uint8_t pid, uint8_t newPriority);
int ps(void);

int waitPid(uint8_t pid);

void* memoryMalloc(uint64_t size);
int memoryFree(void* size);
int memoryStatus(void);

int yield(void);

int createSem(char* name, uint64_t initialValue);
int getSem(char* name);
int postSem(char* name);
int waitSem(char* name);
int closeSem(char* name);

int loopProcess(int* fds);

int createPipe(char* name, int* fds);

#endif