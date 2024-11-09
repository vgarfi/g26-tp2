#ifndef __SPEAKER_H_
#define __SPEAKER_H_

#include <stdint.h>

/**
 * @brief Generates a beep sys_sound from the speaker.
 *
 * @param secs The duration of the beep in seconds.
 * @param freq The frequency of the beep in Hertz.
 */
void beep(uint64_t secs, uint64_t freq);

/**
 * @brief Sends a byte to a specified port.
 *
 * @param memPos The port to send the byte to.
 * @param output The byte to send.
 */
void outb(int memPos, int output);

/**
 * @brief Reads a byte from a specified port.
 *
 * @param memPos The port to read the byte from.
 * @return The byte read from the port.
 */
int inb(int memPos);

#endif