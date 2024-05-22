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

void sleep(int seconds){
	uint64_t sleepStart=rtc_get_seconds(), secondsSlept=0, aux;
	
	while(secondsSlept!=seconds){
		aux=rtc_get_seconds();
		if(aux!=sleepStart){
			sleepStart=aux;
			secondsSlept++;
		}
	}
}