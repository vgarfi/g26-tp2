#ifndef _PROCESS_MODES_H
#define _PROCESS_MODES_H

#include <eliminatorGame.h>
#include <syscalls.h>
#include <testProc.h>
#include <testSync.h>
#include <testMm.h>
#include <loop.h>
#include <utils.h>
#include <phylo.h>
#include <ipc.h>
#include "stdio.h"


int playEliminator(TScope scope);
int processTest(TScope scope);
// ! EASTER EGG
int prioritiesTest(TScope scope);
int memoryTest(TScope scope);
int syncTest(TScope scope);
int loop(TScope scope);
int cat(TScope scope);
int wc(TScope scope);
int filter(TScope scope);
int phylosophers(TScope scope);

#endif