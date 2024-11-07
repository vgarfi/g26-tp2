#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_
#include <stdint.h>
#include <utils.h>


int sysWrite(uint64_t fd, unsigned char* buffer, uint64_t len, uint64_t hexColor);
int sysRead(uint64_t fd, unsigned char* buffer, uint64_t len);
void sysSleep(uint64_t secs, uint64_t ms);
int sysClearScreen();
int sysClearKbEntry();

int sysCtrlPressed();

uint8_t sysUpArrowValue();
uint8_t sysLeftArrowValue();
uint8_t sysDownArrowValue();
uint8_t sysRightArrowValue();
int sysPrintRectangle(int x,int y,int base,int height,uint32_t hexColor);
int sysPrintSquare(int x,int y , int side, uint32_t hexColor);
int sysSetCursorPosition(uint64_t x, uint64_t y);
int sysBeepSound(uint64_t ms, uint64_t freq);

int sysGetSecs(void);
int sysGetMins(void);
int sysGetHour(void);

int sysGetDay(void);
int sysGetMonth(void);
int sysGetYear(void);

int sysZoomIn(void);
int sysZoomOut(void);
int sysGetZoomLevel(void);
int sysSetZoomLevel(int zoomLevel);

int sysPrintRegs(void);
int sysPrintCursor();
int sysHideCursor();
int sysShowCursor();

int sysCreateProcess(char* name, uint64_t argc, char *argv[], int64_t (*code)(int, char**), TScope scope);
uint8_t sysGetCurrentPid(void);
int sysExit(void);

int sysBlockProcess(uint8_t pid);
int sysUnblockProcess(uint8_t pid);
int sysKillProcess(uint8_t pid);
int sysGetScope(uint8_t pid);

int sysNice(uint8_t pid, uint8_t newPriority);
void sysPs(void);

void* sysMalloc(uint64_t size);
void sysFree(void* ptr);
void sysMem(void);

void sysWaitPid(uint8_t pid);

int sysYield(void);

int sysCreateSem(char* name, uint64_t initial_value);
int sysGetSem(char* name);
int sysPostSem(char* name);
int sysWaitSem(char* name);
int sysCloseSem(char* name);

int sysCreatePipe(int* fds, char* name);
int sysSetReadFileDescriptor(uint8_t pid, int fd);
int sysSetWriteFileDescriptor(uint8_t pid, int fd);
int sysClosePipe(char* name);

int sysGetReadFileDescriptor(uint8_t pid);
int sysGetWriteFileDescriptor(uint8_t pid);

#endif