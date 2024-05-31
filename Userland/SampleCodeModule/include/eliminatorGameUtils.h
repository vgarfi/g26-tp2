#include "eliminatorGame.h"

#ifndef __ELIMINATOR_GAME__UTILS_H__
#define __ELIMINATOR_GAME_UTILS_H__

#define DEBOUNCER   100000
#define DIED_TIME   30

void initializeEliminator(void);
void printEliminatorTitle(void);
unsigned char menuOption(void);
void playerDied(int P1Crashed, int P2Crashed, int *scoreP1, int *scoreP2);
void userDied(int* scoreP1);
void wait(void);

int directionIsHorizontal (int direction);

int decideSnakeDirection (int lastDirection, int upArrowValue, int downArrowValue, int leftArrowValue, int rightArrowValue, unsigned char keyPressed);
int decideSnakeDirectionCPU(int lastDirectionP2, SnakeHead snakeHeadCPU, char board[WIDTH][HEIGHT]);

void updateSnakeHead (SnakeHead * head, int direction);

void eliminatorReturn(void);

#endif