// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* sampleCodeModule.c */
#include <stdint.h>
#include <syscalls.h>
#include <stdio.h>
#include <shell.h>

int main() {
	init();
	return 0xDEADBEEF;
}