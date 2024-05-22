#include "eliminatorGame.h"
#include "videoDriver.h"

#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

#define PROV_WIDTH  1000
#define PROV_HEIGHT 600

void eliminatorGame () {
    static char board [PROV_WIDTH][PROV_HEIGHT] = {0};
    printWall();
}

void printWall () {
    for (int i = PROV_WIDTH/2, k = PROV_WIDTH/2; i >= 0 && k < PROV_WIDTH ; i--, k++) {
        vdSetCursor(i, 0);
        vdPrintRect(RED);
        vdSetCursor(k, 0);
        vdPrintRect(RED);
        for (int i = 0; i < 900000; i++)
        {
        }
        
    }   
}
