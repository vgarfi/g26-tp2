// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* _loader.c */
#include <stdint.h>

extern char bss;
extern char endOfBinary;

int main();

void * myMemset(void * destiny, int32_t c, uint64_t length);

int _start() {
	//Clean BSS
	myMemset(&bss, 0, &endOfBinary - &bss);

	return main();

}


void * myMemset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}
