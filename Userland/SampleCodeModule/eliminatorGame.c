#include "include/eliminatorGame.h"
#include "include/eliminatorGameUtils.h"
#include "include/colors.h"

SnakeHead snakeHeadP1;
SnakeHead snakeHeadP2;

int didP1Crashed = 0;
int didP2Crashed = 0;

int lastDirectionP1 = UP;
int lastDirectionP2 = DOWN;

int scoreP1 = 0;
int scoreP2 = 0;

char board [WIDTH][HEIGHT] = {0};

int eliminatorMode = ELIMINATOR_EXEC;

void eliminatorGame () {
    initializeEliminator();
    snakeHeadP1.color = GREEN;
    snakeHeadP2.color = BLUE;
    
    while(eliminatorMode == ELIMINATOR_EXEC) {
        unsigned char option = menuOption();
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
            clearScreen();
            eliminatorMode = !ELIMINATOR_EXEC;
            break;
        } 
    }
    eliminatorMode = ELIMINATOR_EXEC;
    eliminatorReturn();
}

void playAlone(void) {
    unsigned char finishKey;
    unsigned char lastKeyPressed = UP;
    unsigned char keyPressed = lastKeyPressed;
    unsigned char aux;
    
    while (finishKey != ESC) {
        cleanBoard();
        printWall();
        lastDirectionP1 = UP;
        
        snakeHeadP1.x = WIDTH/2;
        snakeHeadP1.y = HEIGHT/2 - HEIGHT/4;

        while (didP1Crashed != CRASHED) {

            printSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            
            if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
                didP1Crashed = CRASHED;
            }

            board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;
            
            for(int i=0; i< DEBOUNCER; i++){
                if(keyPressed == lastKeyPressed){
                    aux = getchar();
                    if(aux!=0)
                        keyPressed=aux;
                }
            }
            lastDirectionP1 = decideSnakeDirection(lastDirectionP1, P1_UP_KEY, P1_DOWN_KEY, P1_LEFT_KEY, P1_RIGHT_KEY, keyPressed);
            updateSnakeHead(&snakeHeadP1, lastDirectionP1);
            lastKeyPressed = keyPressed;
        }

        beepSound(3, 200);
        beepSound(2, 500);
        userDied(&scoreP1);
        didP1Crashed = !CRASHED;

        for (int i = 0; i < DIED_TIME && (finishKey != ESC && finishKey != RESET); i++) {
            finishKey = getchar();
            sleep(0,1);
        }

        if (finishKey == ESC){
            scoreP1 = 0;
            cleanBoard();
        }
        else {
            scoreP1 = (finishKey == RESET) ? 0 : scoreP1;
            finishKey = 0;
        }
    }
}

void playTwoPlayers(int player2) {
    unsigned char finishKey;
    unsigned char keyPressed;
    unsigned char lastDirection, lastKeyPressed, aux;
    while (finishKey != ESC) {

        cleanBoard();
        printWall();
        
        lastDirectionP1 = UP;
        lastDirectionP2 = DOWN;
        
        snakeHeadP1.x = WIDTH/2;
        snakeHeadP1.y = HEIGHT/2 - HEIGHT/4;
        
        snakeHeadP2.x = WIDTH/2;
        snakeHeadP2.y = HEIGHT/2 + HEIGHT/4;
        
        while (didP1Crashed != CRASHED && didP2Crashed != CRASHED) {
            printSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            printSquare(snakeHeadP2.x*SNAKE_HEAD_SIZE, snakeHeadP2.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP2.color);

            if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
                didP1Crashed = CRASHED;
            }

            if (board[snakeHeadP2.x][snakeHeadP2.y] == BLOCKED) {
                didP2Crashed = CRASHED;
            }

            board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;
            board[snakeHeadP2.x][snakeHeadP2.y] = BLOCKED;

            for(int i=0; i< DEBOUNCER; i++){
                if(keyPressed==lastKeyPressed){
                    aux=getchar();
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

        beepSound(2, 200);
        beepSound(1, 500);
        beepSound(1, 570);
        beepSound(2, 320);


        playerDied(didP1Crashed, didP2Crashed, &scoreP1, &scoreP2);
        
        didP1Crashed = !CRASHED;
        didP2Crashed = !CRASHED;
        

        for (int i = 0; i < DIED_TIME && (finishKey != ESC && finishKey != RESET); i++) {
            finishKey = getchar();
            sleep(0,1);
        }

        if (finishKey == ESC) {
            scoreP1 = 0;
            scoreP2 = 0;
            cleanBoard();
        }
        else {
            if (finishKey == RESET) {
                scoreP1 = 0;
                scoreP2 = 0;
            }
            cleanBoard();
            finishKey = 0;
        }
    }
}

void cleanBoard(void) {
    for (int i = 1; i < WIDTH; i++) {
        for (int j = 1; j < HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
    clearScreen();
}

void printWall(void) {
    for (int i = WIDTH/2, k = WIDTH/2; i >= 0 && k < WIDTH ; i--, k++) {
        printSquare(i*WALL_SIZE, 0, WALL_SIZE, RED);
        printSquare(k*WALL_SIZE, 0, WALL_SIZE, RED);
        board[i][0] = BLOCKED;
        board[k][0] = BLOCKED;
        wait();
    }

    for (int i = 0; i < HEIGHT ; i++) {
        printSquare(0, i*WALL_SIZE, WALL_SIZE, RED);
        printSquare((WIDTH-1)*WALL_SIZE, i*WALL_SIZE, WALL_SIZE, RED);
        board[0][i] = BLOCKED;
        board[WIDTH-1][i] = BLOCKED;
        wait();
    }

    for (int i = 0, k = WIDTH-1; i <= WIDTH/2 && k >= WIDTH/2 ; i++, k--) {
        printSquare(i*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);
        printSquare(k*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);

        board[i][HEIGHT-1] = BLOCKED;
        board[k][HEIGHT-1] = BLOCKED;
        wait();
    }   
}
