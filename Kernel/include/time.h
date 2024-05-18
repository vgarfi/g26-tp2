#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

uint64_t rtc_get_seconds();
uint64_t rtc_get_minutes();
uint64_t rtc_get_hour();
uint64_t rtc_get_day();
uint64_t rtc_get_month();
uint64_t rtc_get_year();

#endif
