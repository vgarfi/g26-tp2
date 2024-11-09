#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

/**
 * @brief Handles the timer interrupt.
 */
void timer_handler(void);

/**
 * @brief Gets the elapsed milliseconds since the timer was initialized.
 *
 * @return The elapsed milliseconds.
 */
int ms_elapsed(void);

/**
 * @brief Gets the elapsed seconds since the timer was initialized.
 *
 * @return The elapsed seconds.
 */
int seconds_elapsed(void);

/**
 * @brief Sleeps for a specified number of milliseconds.
 *
 * @param ms The number of milliseconds to sleep.
 */
void sleep(int ms);

/**
 * @brief Initializes the timer.
 */
void initialize_timer(void);

/**
 * @brief Gets the current seconds from the RTC.
 *
 * @return The current seconds.
 */
uint64_t rtc_get_seconds(void);

/**
 * @brief Gets the current minutes from the RTC.
 *
 * @return The current minutes.
 */
uint64_t rtc_get_minutes(void);

/**
 * @brief Gets the current hour from the RTC.
 *
 * @return The current hour.
 */
uint64_t rtc_get_hour(void);

/**
 * @brief Gets the current day from the RTC.
 *
 * @return The current day.
 */
uint64_t rtc_get_day(void);

/**
 * @brief Gets the current month from the RTC.
 *
 * @return The current month.
 */
uint64_t rtc_get_month(void);

/**
 * @brief Gets the current year from the RTC.
 *
 * @return The current year.
 */
uint64_t rtc_get_year(void);

#endif