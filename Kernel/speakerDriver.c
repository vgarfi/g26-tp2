// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>
#include <speaker.h>

 static void play_sound(uint32_t n_frequence) {
 	uint32_t div;
 	uint8_t tmp;
 
 	div = 1193180 / n_frequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (div) );
 	outb(0x42, (uint8_t) (div >> 8));
 
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
 }
 
 void beep(uint64_t ms, uint64_t freq) {
 	 play_sound(freq);
 	 sleep(ms);
 	 nosound();
 }