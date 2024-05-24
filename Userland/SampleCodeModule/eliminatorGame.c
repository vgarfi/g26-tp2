#include <stdio.h>
#include "include/syscalls.h"
#include "include/eliminatorGame.h"
#include "include/string.h"
#include "include/colors.h"

#define PROV_WIDTH          128
#define PROV_HEIGHT         64

#define TICKS_PER_FRAME     1
#define MS_PER_FRAME        2800000

#define BLOCKED 1
#define FREE 0

enum Direction {UP, DOWN, LEFT, RIGHT};

static char board [PROV_WIDTH][PROV_HEIGHT] = {0};

typedef struct {
    uint8_t x;
    uint8_t y;
    uint32_t color;
} SnakeHead;

SnakeHead snakeHeadP1;
SnakeHead snakeHeadP2;

void eliminatorGame () {
    clearScreen();
    
    snakeHeadP1.x = PROV_WIDTH/2;
    snakeHeadP1.y = PROV_HEIGHT/2 - PROV_HEIGHT/4;
    snakeHeadP1.color = GREEN;

    snakeHeadP2.x = PROV_WIDTH/2;
    snakeHeadP2.y = PROV_HEIGHT/2 + PROV_HEIGHT/4;
    snakeHeadP2.color = BLUE;

    showMenu();
}

void playground(){
     int crashed = 0;
    int lastDirectionP1 = RIGHT;

    while (!crashed) {
        setCursorPosition(snakeHeadP1.x, snakeHeadP1.y);
        printRectangle(snakeHeadP1.color);

        
        if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
            crashed = 1;
        }

        board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;

        unsigned char keyPressed = getchar();

        if (keyPressed == 'w') {
            lastDirectionP1 = UP;
        } else if (keyPressed == 's') {
            lastDirectionP1 = DOWN;
        } else if (keyPressed == 'a') {
            lastDirectionP1 = LEFT;
        } else if (keyPressed == 'd') {
            lastDirectionP1 = RIGHT;
        } 

        updateSnakeHead(&snakeHeadP1, lastDirectionP1);
    }

    if (crashed) {
        beepSound(3);
    }
}
void play () {
    int crashed = 0;
    int lastDirectionP1 = RIGHT;
    int lastDirectionP2 = UP;
    int laps = 0;

    while (!crashed) {
        setCursorPosition(snakeHeadP1.x, snakeHeadP1.y);
        printRectangle(snakeHeadP1.color);

        setCursorPosition(snakeHeadP2.x, snakeHeadP2.y);
        printRectangle(snakeHeadP2.color);
        
        if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
            crashed = 1;
        }
        if (board[snakeHeadP2.x][snakeHeadP2.y] == BLOCKED) {
            crashed = 1;
        }

        board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;
        board[snakeHeadP2.x][snakeHeadP2.y] = BLOCKED;

        unsigned char keyPressed = getchar();

        if (keyPressed == 'w') {
            lastDirectionP1 = UP;
        } else if (keyPressed == 's') {
            lastDirectionP1 = DOWN;
        } else if (keyPressed == 'a') {
            lastDirectionP1 = LEFT;
        } else if (keyPressed == 'd') {
            lastDirectionP1 = RIGHT;
        }

        updateSnakeHead(&snakeHeadP1, lastDirectionP1);
        updateSnakeHead(&snakeHeadP2, lastDirectionP2);
        laps++;
    }

    if (crashed) {
        beepSound(3);
    }
}

void play2(){

    int crashed = 0;
    int lastDirectionP1 = RIGHT;
    int lastDirectionP2 = DOWN;
    int laps = 0;

    while (!crashed) {
        setCursorPosition(snakeHeadP1.x, snakeHeadP1.y);
        printRectangle(snakeHeadP1.color);

        setCursorPosition(snakeHeadP2.x, snakeHeadP2.y);
        printRectangle(snakeHeadP2.color);
        sleep(0, TICKS_PER_FRAME);


        if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
            crashed = 1;
        }
        if (board[snakeHeadP2.x][snakeHeadP2.y] == BLOCKED) {
            crashed = 1;
        }

        board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;
        board[snakeHeadP2.x][snakeHeadP2.y] = BLOCKED;

        if (laps % 8 == 0) { // Cada 4 cambio la direc per codere
            int ranDirect =  generateRandom(21, snakeHeadP1.x * snakeHeadP1.y);
            if (directionIsHorizontal(lastDirectionP1)) {
                if (ranDirect % 2) {
                    lastDirectionP1 = UP;
                } else {
                    lastDirectionP1 = DOWN;
                }
            } else {
                if (ranDirect % 2) {
                    lastDirectionP1 = LEFT;
                } else {
                    lastDirectionP1 = RIGHT;
                }
            }

            ranDirect =  generateRandom(888, snakeHeadP2.x * snakeHeadP2.y);
            if (directionIsHorizontal(lastDirectionP2)) {
                if (ranDirect % 3) {
                    lastDirectionP2 = UP;
                } else {
                    lastDirectionP2 = DOWN;
                }
            } else {
                if (ranDirect % 3) {
                    lastDirectionP2 = LEFT;
                } else {
                    lastDirectionP2 = RIGHT;
                }
            }
        }
        updateSnakeHead(&snakeHeadP1, lastDirectionP1);
        updateSnakeHead(&snakeHeadP2, lastDirectionP2);
        laps++;
    }

    if (crashed) {
        beepSound(3);
    }
}
int generateRandom (int a, int b) {
    return a * b + 1;
}
int directionIsHorizontal (int direction) {
    return direction == LEFT || direction == RIGHT;
}

void updateSnakeHead (SnakeHead * head, int direction) {
    switch (direction)
    {
    case UP:
        head->y--;
        break;
    case DOWN:
        head->y++;
        break;
    case LEFT:
        head->x--;
        break;
    case RIGHT:
        head->x++;
        break;
    default:
        break;
    }
}

void printWall () {
    
    for (int i = PROV_WIDTH/2, k = PROV_WIDTH/2; i >= 0 && k < PROV_WIDTH ; i--, k++) {
        setCursorPosition(i, 0);
        printRectangle(RED);
        setCursorPosition(k, 0);
        printRectangle(RED);

        board[i][0] = BLOCKED;
        board[k][0] = BLOCKED;
        wait();
        
    }

    for (int i = 0; i < PROV_HEIGHT ; i++) {
        setCursorPosition(0, i);
        printRectangle(RED);
        setCursorPosition(PROV_WIDTH-1, i);
        printRectangle(RED);
        board[0][i] = BLOCKED;
        board[PROV_WIDTH-1][i] = BLOCKED;
        wait();
    }

    for (int i = 0, k = PROV_WIDTH-1; i <= PROV_WIDTH/2 && k >= PROV_WIDTH/2 ; i++, k--) {
        setCursorPosition(i, PROV_HEIGHT-1);
        printRectangle(RED);
        setCursorPosition(k, PROV_HEIGHT-1);
        printRectangle(RED);

        board[i][PROV_HEIGHT-1] = BLOCKED;
        board[k][PROV_HEIGHT-1] = BLOCKED;
        wait();
    }   
}



void printEliminatorTitle() {
    // Representación de cada letra en píxeles
    char* letters[] = {
        // E
        "1111\n"
        "1000\n"
        "1110\n"
        "1000\n"
        "1111\n",
        // L
        "1000\n"
        "1000\n"
        "1000\n"
        "1000\n"
        "1111\n",
        // I
        "0110\n"
        "0110\n"
        "0110\n"
        "0110\n"
        "0110\n",
        // M
        "10001\n"
        "11011\n"
        "10101\n"
        "10001\n"
        "10001\n",
        // I
        "0110\n"
        "0110\n"
        "0110\n"
        "0110\n"
        "0110\n",
        // N
        "10001\n"
        "11001\n"
        "10101\n"
        "10011\n"
        "10001\n",
        // A
        "01110\n"
        "10001\n"
        "11111\n"
        "10001\n"
        "10001\n",
        // T
        "11111\n"
        "00100\n"
        "00100\n"
        "00100\n"
        "00100\n",
        // O
        "01110\n"
        "10001\n"
        "10001\n"
        "10001\n"
        "01110\n",
        // R
        "11110\n"
        "10001\n"
        "11110\n"
        "10010\n"
        "10001\n"
    };

    int startX = PROV_WIDTH / 2 - (4 + 3) * 10 / 2; // Centra la palabra en la pantalla, 4 = anchp de letra, 3 = espacio entre letras
    int startY = PROV_HEIGHT / 2 - 5 / 2;

    for (int l = 0; l <= 9; l++) {
        int x = startX + l * 7; // 6 permite un espacio entre las letras
        int y = startY;

        sleep(0, 2*TICKS_PER_FRAME);
        // Recorre cada píxel de la letra
        for (int i = 0; letters[l][i] != '\0'; i++) {
            if (letters[l][i] == '1') {
                setCursorPosition(x, y);
                printRectangle(RED);
            }

            if (letters[l][i] == '\n') {
                // Al final de una línea, mueve el cursor a la siguiente línea
                x = startX + l * 7;
                y++;
            } else {
                // En medio de una línea, mueve el cursor a la derecha
                x++;
            }
        }
    }
}

void showMenu(){
    printEliminatorTitle();

    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 5);
    print("Welcome to the Eliminator Game\n");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 6);
    print("Press 1 to play alone\n");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 7);
    print("Press 2 to play against a friend\n"); // TODO
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 8);
    print("Press 3 to play against a computer\n");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 9);
    print("Press ESC to exit\n"); // TODO
    char option = getchar();
    while (option != '1' && option != '2' && option != '3' && option != 27) {
        option = getchar();
    }
    
    if (option == '1') {
        clearScreen();
        printWall();
        playground();
    } else if (option == '2') {
        clearScreen();
        printWall();
        play2();
    } else if (option == 27){
        clearScreen();
    }

}

void wait(){ // TODO deberímos poder manejar esto con sleep. De probar paráemtros, esta resultó una buena alternativa
   for (size_t i = 0; i < MS_PER_FRAME; i++) {
   }
}