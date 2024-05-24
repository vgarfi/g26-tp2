#include "include/time.h"
#include <interrupts.h>
#include <stdint.h>

enum months {JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

static unsigned long ticks = 0;

char timeFormat[]="HH:MM:SS";
char dateFormat[]="DD/MM/YY";

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

static int setHoursToTimezone(int hours){
	switch(hours){
		case 0: return 21;
		case 1: return 22;
		case 2: return 23;
		default: return hours-TIMEZONEDIF;
	}
}

static int has31days(int month){
	return month==JAN || month==MAR || month==MAY || month==JUL || month==AUG || month==OCT || month==DEC;
}

static void setDateToTimezone(int* year, int* month, int* days){
	int hours = rtc_get_hour();
	if(hours<3 && hours>=0){		// If time is a day ahead of our timezone, we adjust the date
		if(*month==JAN && *days==1){
			*days=31;
			*month=DEC;
			*year=*year==0?99:*year-1;
		}
		else if(*month==MAR && *days==1){
			*days=29;
			*month=FEB;
		}
		else if(has31days(*month-1) && *days==1){
			*days=31;
			(*month)--;
		}
		else if(*days==1){
			*days=30;
			(*month)--;
		}
		else{
			(*days)--;
		}
	}
}

char * getCurrentTime(){
	int seconds=rtc_get_seconds(),minutes=rtc_get_minutes(),hours=rtc_get_hour();
	hours=setHoursToTimezone(hours);
	//set Hours
	timeFormat[0]=hours/10 + '0';
	timeFormat[1]=hours%10 + '0';
	
	//set Minutes
	timeFormat[3]=minutes/10 + '0';
	timeFormat[4]=minutes%10 + '0';

	//set Seconds
	timeFormat[6]=seconds/10 + '0';
	timeFormat[7]=seconds%10 + '0';

	return timeFormat;
}

char * getCurrentDate(){
	int days=rtc_get_day(), month=rtc_get_month(), year=rtc_get_year();
	setDateToTimezone(&year, &month, &days);
	//set Days
	dateFormat[0]=days/10 + '0';
	dateFormat[1]=days%10 + '0';

	// set Months
	dateFormat[3]=month/10 + '0';
	dateFormat[4]=month%10 + '0';

	// set Year
	dateFormat[6]=year/10 + '0';
	dateFormat[7]=year%10 + '0';

	return dateFormat;
}