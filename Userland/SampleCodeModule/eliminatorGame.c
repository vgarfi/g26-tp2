// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/eliminatorGame.h"
#include "include/eliminatorGameUtils.h"
#include "include/colors.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/utils.h"

SnakeHead snakeHeadP1;
SnakeHead snakeHeadP2;

int didP1Crashed = 0;
int didP2Crashed = 0;

int lastDirectionP1 = UP;
int lastDirectionP2 = DOWN;

int scoreP1 = 0;
int scoreP2 = 0;

char board [WIDTH][HEIGHT] = {{0}};
int map;

int eliminatorMode = ELIMINATOR_EXEC;

void eliminatorGame () {
    initializeEliminator();
    snakeHeadP1.color = GREEN;
    snakeHeadP2.color = BLUE;
    
    while(eliminatorMode == ELIMINATOR_EXEC) {
        unsigned char option = menuOption(&map);
        switch (option) {
        case ONE_PLAYER:
            playAlone();
            break;
        
        case TWO_PLAYERS:
            playTwoPlayers(HUMAN);
            break;
        
        case COMPUTER:
            playTwoPlayers(CPU);
            break;
        
        case ESC:
            sysClearScreen();
            eliminatorMode = !ELIMINATOR_EXEC;
            break;
        } 
    }
    eliminatorMode = ELIMINATOR_EXEC;
    eliminatorReturn();
}

void playAlone(void) {
    char finishKey = UP;
    char lastKeyPressed = UP;
    char keyPressed = lastKeyPressed;
    char aux;
    
    while (finishKey != ESC) {
        cleanBoard();
        printWall();
        lastDirectionP1 = UP;
        
        snakeHeadP1.x = WIDTH/2;
        snakeHeadP1.y = HEIGHT/2 - HEIGHT/4;

        while (didP1Crashed != CRASHED) {

            sysPrintSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            
            if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED_SPACE) {
                didP1Crashed = CRASHED;
            }

            board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED_SPACE;
            
            for(int i=0; i< DEBOUNCER; i++){
                if(keyPressed == lastKeyPressed){
                    aux = getcharNoBlock();
                    if(aux!=0)
                        keyPressed=aux;
                }
            }
            lastDirectionP1 = decideSnakeDirection(lastDirectionP1, P1_UP_KEY, P1_DOWN_KEY, P1_LEFT_KEY, P1_RIGHT_KEY, keyPressed);
            updateSnakeHead(&snakeHeadP1, lastDirectionP1);
            lastKeyPressed = keyPressed;
        }

        sysBeepSound(3, DO);
        sysBeepSound(2, SI);
        
        userDied(&scoreP1);
        didP1Crashed = !CRASHED;

        while (finishKey != ESC && finishKey != RESET && finishKey != SPACE) {
            finishKey = getcharNoBlock();
        }

        if (finishKey != ESC) {
            scoreP1 = (finishKey == RESET)? 0 : scoreP1;
            sysBeepSound(1, LA);
            sysBeepSound(1, SI);
            sysBeepSound(1, FA);
            finishKey = 0;
            keyPressed = UP;
        }

    }
    scoreP1 = 0;
    cleanBoard();
}

void playTwoPlayers(int player2) {
    unsigned char finishKey = UP;
    unsigned char keyPressed = UP;
    unsigned char lastKeyPressed = UP, aux;
    while (finishKey != ESC) {

        cleanBoard();
        printWall();
        
        lastDirectionP1 = UP;
        lastDirectionP2 = DOWN;

        int height_2 = HEIGHT/2;
        int height_4 = HEIGHT/4;
        
        snakeHeadP1.x = snakeHeadP2.x = WIDTH/2;
        snakeHeadP1.y = height_2 - height_4;
        
        snakeHeadP2.y = height_2 + height_4;
        
        while (didP1Crashed != CRASHED && didP2Crashed != CRASHED) {
            sysPrintSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            sysPrintSquare(snakeHeadP2.x*SNAKE_HEAD_SIZE, snakeHeadP2.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP2.color);

            if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED_SPACE) {
                didP1Crashed = CRASHED;
            }

            if (board[snakeHeadP2.x][snakeHeadP2.y] == BLOCKED_SPACE) {
                didP2Crashed = CRASHED;
            }

            board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED_SPACE;
            board[snakeHeadP2.x][snakeHeadP2.y] = BLOCKED_SPACE;

            for(int i=0; i< DEBOUNCER; i++){
                if(keyPressed==lastKeyPressed){
                    aux=getcharNoBlock();
                    if(aux!=0){
                        keyPressed=aux;
                    }
                }
            }            
            lastDirectionP1 = decideSnakeDirection(lastDirectionP1, P1_UP_KEY, P1_DOWN_KEY, P1_LEFT_KEY, P1_RIGHT_KEY, keyPressed);
            lastDirectionP2 = (player2 == CPU) ? decideSnakeDirectionCPU(lastDirectionP2, snakeHeadP2, board) : decideSnakeDirection(lastDirectionP2, P2_UP_KEY, P2_DOWN_KEY, P2_LEFT_KEY, P2_RIGHT_KEY, keyPressed);
            
            updateSnakeHead(&snakeHeadP1, lastDirectionP1);
            updateSnakeHead(&snakeHeadP2, lastDirectionP2);
            lastKeyPressed=keyPressed;
        }

        twoPlayersSound(didP1Crashed, didP2Crashed, player2);

        playerDied(didP1Crashed, didP2Crashed, &scoreP1, &scoreP2);
        
        didP1Crashed = !CRASHED;
        didP2Crashed = !CRASHED;
        

        while (finishKey != ESC && finishKey != RESET && finishKey != SPACE) {
            finishKey = getcharNoBlock();
        }

        if (finishKey != ESC) {
            scoreP1 = (finishKey == RESET)? 0 : scoreP1;
            scoreP2 = (finishKey == RESET)? 0 : scoreP2;
            sysBeepSound(1, LA);
            sysBeepSound(1, SI);
            sysBeepSound(1, FA);
            finishKey = 0;
            keyPressed = UP;
        }
    }
    scoreP1 = 0;
    scoreP2 = 0;
    cleanBoard();
}

void cleanBoard(void) {
    for (int i = 1; i < WIDTH; i++) {
        for (int j = 1; j < HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
    sysClearScreen();
}

void printWall(void) {
    for (int i = WIDTH/2, k = WIDTH/2; i >= 0 && k < WIDTH ; i--, k++) {
        sysPrintSquare(i*WALL_SIZE, 0, WALL_SIZE, RED);
        sysPrintSquare(k*WALL_SIZE, 0, WALL_SIZE, RED);
        board[i][0] = BLOCKED_SPACE;
        board[k][0] = BLOCKED_SPACE;
        wait();
    }

    for (int i = 0; i < HEIGHT ; i++) {
        sysPrintSquare(0, i*WALL_SIZE, WALL_SIZE, RED);
        sysPrintSquare((WIDTH-1)*WALL_SIZE, i*WALL_SIZE, WALL_SIZE, RED);
        board[0][i] = BLOCKED_SPACE;
        board[WIDTH-1][i] = BLOCKED_SPACE;
        wait();
    }

    for (int i = 0, k = WIDTH-1; i <= WIDTH/2 && k >= WIDTH/2 ; i++, k--) {
        sysPrintSquare(i*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);
        sysPrintSquare(k*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);

        board[i][HEIGHT-1] = BLOCKED_SPACE;
        board[k][HEIGHT-1] = BLOCKED_SPACE;
        wait();
    }

    if (map == MAP_B) {
        int boxSize = 5;
        int offsets[] = {1, 3, 5, 7, 9};
        for (int k = 0; k < 5; k++) {
            int startX = offsets[k] * WIDTH / 10;
            int startY = offsets[(k+2)%5] * HEIGHT / 10;
            for (int i = startX; i < startX + boxSize; i++) {
                sysPrintSquare(i*WALL_SIZE, startY*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY] = BLOCKED_SPACE;
                sysPrintSquare(i*WALL_SIZE, (startY + boxSize - 1)*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY + boxSize - 1] = BLOCKED_SPACE;
                wait();
            }
            for (int j = startY; j < startY + boxSize; j++) {
                sysPrintSquare(startX*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX][j] = BLOCKED_SPACE;
                sysPrintSquare((startX + boxSize - 1)*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX + boxSize - 1][j] = BLOCKED_SPACE;
                wait();
            }
        }
    }

    if (map == MAP_C) {
        
        int lineLength = WIDTH / 8;
        int offsets[] = {1, 3, 5, 7};
        for (int k = 0; k < 4; k++) {
            int startX = offsets[k] * WIDTH / 9;
            int startY = offsets[(k+2)%4] * HEIGHT / 10;
            
            for (int i = startX; i < startX + lineLength; i++) {
                sysPrintSquare(i*WALL_SIZE, startY*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY] = BLOCKED_SPACE;
                wait();
            }
            
            for (int j = startY; j < startY + lineLength; j++) {
                sysPrintSquare(startX*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX][j] = BLOCKED_SPACE;
                wait();
            }
        }
    }
}
