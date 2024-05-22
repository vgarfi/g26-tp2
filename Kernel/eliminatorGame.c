#include "eliminatorGame.h"
#include "videoDriver.h"

#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

#define PROV_WIDTH  128
#define PROV_HEIGHT 64
static char board [PROV_WIDTH][PROV_HEIGHT] = {0};

void eliminatorGame () {
    printWall();
}

void printWall () {
    for (int i = PROV_WIDTH/2, k = PROV_WIDTH/2; i >= 0 && k < PROV_WIDTH ; i--, k++) {
        vdSetCursor(i, 0);
        vdPrintRect(RED);
        vdSetCursor(k, 0);
        vdPrintRect(RED);

        board[i][0] = 1;
        board[k][0] = 1;
        for (int i = 0; i < 900000; i++)
        {
        }
        
    }

    for (int i = 0; i < PROV_HEIGHT ; i++) {
        vdSetCursor(0, i);
        vdPrintRect(RED);
        vdSetCursor(PROV_WIDTH-1, i);
        vdPrintRect(RED);
        board[0][i] = 1;
        board[PROV_WIDTH-1][i] = 1;
        for (int i = 0; i < 900000; i++)
        {
        }
        vdSetCursor(PROV_WIDTH/2 + i, 100);
        vdPrintChar('c');
    }

    for (int i = 0, k = PROV_WIDTH-1; i <= PROV_WIDTH/2 && k >= PROV_WIDTH/2 ; i++, k--) {
        vdSetCursor(i, PROV_HEIGHT-1);
        vdPrintRect(RED);
        vdSetCursor(k, PROV_HEIGHT-1);
        vdPrintRect(RED);

        board[i][PROV_HEIGHT-1] = 1;
        board[k][PROV_HEIGHT-1] = 1;
        for (int i = 0; i < 900000; i++)
        {
        }
        
    }   
}

void showMenu(){
    vdPrint("Eliminator", GREEN);
    vdNewLine();
    vdPrint("Indique la cantidad de jugadores", GREEN);
    vdNewLine();
    vdPrint("[1] (un jugador) [2] (2 jugadores)", GREEN);
    
}
