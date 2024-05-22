#include <time.h>
#include <interrupts.h>
#include <stdint.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void sleep(int ticksToSleep){
	long start = ticks;
	while((ticks-start)!=ticksToSleep){
		_hlt();
	}
}