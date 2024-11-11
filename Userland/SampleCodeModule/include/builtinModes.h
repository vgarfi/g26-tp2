#ifndef _BUILTIN_MODES_H
#define _BUILTIN_MODES_H

#include <dateTime.h>
#include <exceptions.h>
#include <syscalls.h>
#include <colors.h>
#include "stdio.h"
#include "shell.h"
#include <lib.h>

void help (void);
void playEasterEgg(void);
void clear(void);
void time(void);

void date(void);
void zoomin(void);
void zoomout(void);
void divByZero(void);
void invalidOp(void);
void registers(void);
void notFound(char* commandNotFound);
void psPrinting(void);
void mem(void);
void blockp(void);
void unblockp(void);
void nicep(void);
void killp(void);

#endif