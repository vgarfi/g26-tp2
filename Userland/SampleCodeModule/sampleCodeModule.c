/* sampleCodeModule.c */
#include <stdint.h>

int waitNano(int seconds);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void ncPrintChar(char character)
{
	*currentVideo = character;
	currentVideo += 2;
}

void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

int main() {
	//All the following code may be removed 

/*
	ncPrint("ESPERANDO 5 SEGUNDOS...");
	waitNano(5);
	ncPrint("FINALIZADO");		
*/
	return 0xDEADBEEF;
}