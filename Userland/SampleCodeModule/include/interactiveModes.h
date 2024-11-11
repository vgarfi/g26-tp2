#ifndef MODES_H
#define MODES_H

#include <processModes.h>
#include <eliminatorGame.h>
#include <syscalls.h>
#include <testProc.h>
#include <testSync.h>
#include <testMm.h>
#include <loop.h>
#include <utils.h>
#include <phylo.h>
#include <ipc.h>
#include <stdio.h>
#include "shell.h"


void pipeProcesses(char* input);
void createBackgroundProcess(char* input);

#endif
