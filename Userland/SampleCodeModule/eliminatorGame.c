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
            sysclearScreen();
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

            sysprintSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            
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

        sysbeepSound(3, DO);
        sysbeepSound(2, SI);
        
        userDied(&scoreP1);
        didP1Crashed = !CRASHED;

        while (finishKey != ESC && finishKey != RESET && finishKey != SPACE) {
            finishKey = getchar();
        }

        if (finishKey != ESC) {
            scoreP1 = (finishKey == RESET)? 0 : scoreP1;
            sysbeepSound(1, LA);
            sysbeepSound(1, SI);
            sysbeepSound(1, FA);
            finishKey = 0;
        }

    }
    scoreP1 = 0;
    cleanBoard();
}

void playTwoPlayers(int player2) {
    unsigned char finishKey;
    unsigned char keyPressed;
    unsigned char lastKeyPressed, aux;
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
            sysprintSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            sysprintSquare(snakeHeadP2.x*SNAKE_HEAD_SIZE, snakeHeadP2.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP2.color);

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

        twoPlayersSound(didP1Crashed, didP2Crashed, player2);

        playerDied(didP1Crashed, didP2Crashed, &scoreP1, &scoreP2);
        
        didP1Crashed = !CRASHED;
        didP2Crashed = !CRASHED;
        

        while (finishKey != ESC && finishKey != RESET && finishKey != SPACE) {
            finishKey = getchar();
        }

        if (finishKey != ESC) {
            scoreP1 = (finishKey == RESET)? 0 : scoreP1;
            scoreP2 = (finishKey == RESET)? 0 : scoreP2;
            sysbeepSound(1, LA);
            sysbeepSound(1, SI);
            sysbeepSound(1, FA);
            finishKey = 0;
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
    sysclearScreen();
}

void printWall(void) {
    for (int i = WIDTH/2, k = WIDTH/2; i >= 0 && k < WIDTH ; i--, k++) {
        sysprintSquare(i*WALL_SIZE, 0, WALL_SIZE, RED);
        sysprintSquare(k*WALL_SIZE, 0, WALL_SIZE, RED);
        board[i][0] = BLOCKED;
        board[k][0] = BLOCKED;
        wait();
    }

    for (int i = 0; i < HEIGHT ; i++) {
        sysprintSquare(0, i*WALL_SIZE, WALL_SIZE, RED);
        sysprintSquare((WIDTH-1)*WALL_SIZE, i*WALL_SIZE, WALL_SIZE, RED);
        board[0][i] = BLOCKED;
        board[WIDTH-1][i] = BLOCKED;
        wait();
    }

    for (int i = 0, k = WIDTH-1; i <= WIDTH/2 && k >= WIDTH/2 ; i++, k--) {
        sysprintSquare(i*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);
        sysprintSquare(k*WALL_SIZE, (HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);

        board[i][HEIGHT-1] = BLOCKED;
        board[k][HEIGHT-1] = BLOCKED;
        wait();
    }

    if (map == MAP_B) {
        int boxSize = 5;
        int offsets[] = {1, 3, 5, 7, 9};
        for (int k = 0; k < 5; k++) {
            int startX = offsets[k] * WIDTH / 10;
            int startY = offsets[(k+2)%5] * HEIGHT / 10;
            for (int i = startX; i < startX + boxSize; i++) {
                sysprintSquare(i*WALL_SIZE, startY*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY] = BLOCKED;
                sysprintSquare(i*WALL_SIZE, (startY + boxSize - 1)*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY + boxSize - 1] = BLOCKED;
                wait();
            }
            for (int j = startY; j < startY + boxSize; j++) {
                sysprintSquare(startX*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX][j] = BLOCKED;
                sysprintSquare((startX + boxSize - 1)*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX + boxSize - 1][j] = BLOCKED;
                wait();
            }
        }
    }

    if (map == MAP_C) {
        // Líneas y formas que no bloquean el juego
        int lineLength = WIDTH / 5; // Longitud de la línea
        int offsets[] = {1, 3, 5, 7}; // Posiciones más alejadas del centro
        for (int k = 0; k < 4; k++) {
            int startX = offsets[k] * WIDTH / 8;
            int startY = offsets[(k+2)%4] * HEIGHT / 8;
            // Dibujar una línea horizontal
            for (int i = startX; i < startX + lineLength; i++) {
                sysprintSquare(i*WALL_SIZE, startY*WALL_SIZE, WALL_SIZE, YELLOW);
                board[i][startY] = BLOCKED;
                wait();
            }
            // Dibujar una línea vertical
            for (int j = startY; j < startY + lineLength; j++) {
                sysprintSquare(startX*WALL_SIZE, j*WALL_SIZE, WALL_SIZE, YELLOW);
                board[startX][j] = BLOCKED;
                wait();
            }
        }
    }
}
