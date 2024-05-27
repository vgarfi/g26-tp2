#include <stdio.h>
#include "include/syscalls.h"
#include "include/eliminatorGame.h"
#include "include/string.h"
#include "include/colors.h"


#define TICKS_PER_FRAME     1
#define MS_PER_FRAME        180000

#define BLOCKED             1
#define FREE                0

#define SNAKE_HEAD_SIZE     8
#define WALL_SIZE           8


#define PROV_WIDTH          1024
#define PROV_HEIGHT         768

#define CRASHED             1

enum Direction {UP, DOWN, LEFT, RIGHT};

enum Player {CPU, HUMAN};

static char board [PROV_WIDTH][PROV_HEIGHT] = {0};

typedef struct {
    uint8_t x;
    uint8_t y;
    uint32_t color;
} SnakeHead;

SnakeHead snakeHeadP1;
SnakeHead snakeHeadP2;

int didP1Crashed = 0;
int didP2Crashed = 0;

int lastDirectionP1 = UP;
int lastDirectionP2 = DOWN;

int scoreP1 = 0;
int scoreP2 = 0;

int decideSnakeDirection (int lastDirection, int upArrowValue, int downArrowValue, int leftArrowValue, int rightArrowValue, unsigned char keyPressed);

void eliminatorGame () {
    clearScreen();
    snakeHeadP1.color = GREEN;
    snakeHeadP2.color = BLUE;
    showMenu();
}

void playAlone() {
    unsigned char finishKey;
    unsigned char lastKeyPressed;
    while (finishKey != 27) {
        cleanBoard();
        printWall();
        lastDirectionP1 = UP;
        snakeHeadP1.x = PROV_WIDTH/2;
        snakeHeadP1.y = PROV_HEIGHT/2 - PROV_HEIGHT/4;

        while (didP1Crashed != CRASHED) {

            printSquare(snakeHeadP1.x*SNAKE_HEAD_SIZE, snakeHeadP1.y*SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, snakeHeadP1.color);
            
            if (board[snakeHeadP1.x][snakeHeadP1.y] == BLOCKED) {
                didP1Crashed = CRASHED;
            }

            board[snakeHeadP1.x][snakeHeadP1.y] = BLOCKED;
            
            unsigned char keyPressed = getchar();
            lastDirectionP1 = decideSnakeDirection(lastDirectionP1, upArrowValue(), downArrowValue(), leftArrowValue(), rightArrowValue(), keyPressed);
            updateSnakeHead(&snakeHeadP1, lastDirectionP1);

            lastKeyPressed = keyPressed;
        }

        beepSound(3);
        userDied();

        for (size_t i = 0; i < 30 && (finishKey != 27 && finishKey != 'r'); i++) {
            finishKey = getchar();
            sleep(0,1);
        }

        if (finishKey == 27) {
            scoreP1 = 0;
            clearScreen();
            showMenu();
        }
        else {
            scoreP1 = finishKey == 'r' ? 0 : scoreP1;
            finishKey = 0;
        }
    }
}


void playerDied(int P1Crashed, int P2Crashed) {
    printRectangle(
        PROV_WIDTH / 2 - 10, 
        PROV_HEIGHT / 2 - 5, 
        20*WALL_SIZE, 
        10*WALL_SIZE, 
        GREY
    );
    if (P1Crashed == CRASHED && P2Crashed == CRASHED) {
        setCursorPosition(PROV_WIDTH / 2 - 5, PROV_HEIGHT / 2 - 3);
        print("DRAW!");
    } else if (P1Crashed == CRASHED) {
        setCursorPosition(PROV_WIDTH / 2 - 5, PROV_HEIGHT / 2 - 3);
        print("PLAYER 2 WINS!");
        scoreP2++;
    } else {
        setCursorPosition(PROV_WIDTH / 2 - 5, PROV_HEIGHT / 2 - 3);
        print("PLAYER 1 WINS!");
        scoreP1++;
    }

    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2-1);
    print("P1 SCORE is: ");
    char score[10];
    itoa(scoreP1, score);
    print(score);
    print(" P2 SCORE is: ");
    itoa(scoreP2, score);
    print(score);

    didP1Crashed = !CRASHED;
    didP2Crashed = !CRASHED;
    
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2);
    print("Press R to restart");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2+1);
    print("Press ESC to exit");
    
    // TODO cambiar a texto tipo ELIMINTARO con la palabra YOU DIED!
    
}

void userDied() {
    printRectangle(
        PROV_WIDTH / 2 - 10, 
        PROV_HEIGHT / 2 - 5, 
        20*WALL_SIZE, 
        10*WALL_SIZE, 
        GREY
    );
    scoreP1++;
    didP1Crashed = !CRASHED;
    setCursorPosition(PROV_WIDTH / 2 - 5, PROV_HEIGHT / 2 - 2);
    print("YOU DIED!");
    
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2);
    print("Your DEATHS are: ");
    char score[10];
    itoa(scoreP1, score);
    print(score);

    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2+1);
    print("Press R to restart");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2+2);
    print("Press ESC to exit");
    
    // TODO cambiar a texto tipo ELIMINTARO con la palabra YOU DIED!
    
}

void cleanBoard() {
    for (int i = 1; i < PROV_WIDTH; i++) {
        for (int j = 1; j < PROV_HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
    clearScreen();
}

int decideSnakeDirection (int lastDirection, int upArrowValue, int downArrowValue, int leftArrowValue, int rightArrowValue, unsigned char keyPressed) {
    if (directionIsHorizontal(lastDirection)) {
        if (keyPressed == upArrowValue) {
            return UP;
        } else if (keyPressed == downArrowValue) {
            return DOWN;
        }
        else return lastDirection;
    } else {
        if (keyPressed == leftArrowValue) {
            return LEFT;
        } else if (keyPressed == rightArrowValue) {
            return RIGHT;
        }
        else return lastDirection;
    }
}

void playTwoPlayers(int player2){
    unsigned char finishKey;
    while (finishKey != 27) {
        cleanBoard();
        printWall();
        lastDirectionP1 = UP;
        lastDirectionP2 = DOWN;
        snakeHeadP1.x = PROV_WIDTH/2;
        snakeHeadP1.y = PROV_HEIGHT/2 - PROV_HEIGHT/4;
        snakeHeadP2.x = PROV_WIDTH/2;
        snakeHeadP2.y = PROV_HEIGHT/2 + PROV_HEIGHT/4;
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

            unsigned char keyPressed = getchar();
            
            lastDirectionP1 = decideSnakeDirection(lastDirectionP1, upArrowValue(), downArrowValue(), leftArrowValue(), rightArrowValue(), keyPressed);
            lastDirectionP2 = (player2 == CPU) ? decideSnakeDirectionCPU(lastDirectionP2) : decideSnakeDirection(lastDirectionP2, 'w', 's', 'a', 'd', keyPressed);
            
            updateSnakeHead(&snakeHeadP1, lastDirectionP1);
            updateSnakeHead(&snakeHeadP2, lastDirectionP2);
        }

        beepSound(3);
        playerDied(didP1Crashed, didP2Crashed);
        

        for (size_t i = 0; i < 30 && (finishKey != 27 && finishKey != 'r'); i++) {
            finishKey = getchar();
            sleep(0,1);
        }

        if (finishKey == 27) {
            scoreP1 = 0;
            scoreP2 = 0;
            cleanBoard();
            showMenu();
        }
        else {
            if (finishKey == 'r') {
                scoreP1 = 0;
                scoreP2 = 0;
            }
            cleanBoard();

            finishKey = 0;
        }
    }
}

int decideSnakeDirectionCPU(int lastDirectionP2) {
    
    switch (lastDirectionP2) {
    case UP: 
        if (board[snakeHeadP2.x-1][snakeHeadP2.y] == BLOCKED)
            return LEFT;
        break;
    case DOWN:
        if (board[snakeHeadP2.x+1][snakeHeadP2.y] == BLOCKED)
            return RIGHT;
        break;
    case LEFT:
        if (board[snakeHeadP2.x][snakeHeadP2.y-1] == BLOCKED)
            return DOWN;
        break;
    case RIGHT:
        if (board[snakeHeadP2.x][snakeHeadP2.y+1] == BLOCKED)
            return UP;
        break;
    default:
        return lastDirectionP2;
        break;
    }
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
        printSquare(i*WALL_SIZE, 0, WALL_SIZE, RED);
        printSquare(k*WALL_SIZE, 0, WALL_SIZE, RED);
        board[i][0] = BLOCKED;
        board[k][0] = BLOCKED;
        wait();
        
    }

    for (int i = 0; i < PROV_HEIGHT ; i++) {
        printSquare(0, i*WALL_SIZE, WALL_SIZE, RED);
        printSquare((PROV_WIDTH-1)*WALL_SIZE, i*WALL_SIZE, WALL_SIZE, RED);
        board[0][i] = BLOCKED;
        board[PROV_WIDTH-1][i] = BLOCKED;
        wait();
    }

    for (int i = 0, k = PROV_WIDTH-1; i <= PROV_WIDTH/2 && k >= PROV_WIDTH/2 ; i++, k--) {
        printSquare(i*WALL_SIZE, (PROV_HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);
        printSquare(k*WALL_SIZE, (PROV_HEIGHT-1)*WALL_SIZE, WALL_SIZE, RED);

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
        for (int i = 0; letters[l][i] != '\0'; i++) {
            if (letters[l][i] == '1') {
                printSquare(x+SNAKE_HEAD_SIZE, y+SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE, RED);
            }

            if (letters[l][i] == '\n') {
                x = startX + l * 7;
                y++;
            } else {
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
    print("Press 2 to play against a friend\n");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 8);
    print("Press 3 to play against a computer\n");
    setCursorPosition(PROV_WIDTH / 2 - 10, PROV_HEIGHT / 2 + 9);
    print("Press ESC to exit\n");
    char option = getchar();
    while (option != '1' && option != '2' && option != '3' && option != 27) {
        option = getchar();
    }
    
    if (option == '1') {
        clearScreen();
        playAlone();
    } else if (option == '2') {
        clearScreen();
        playTwoPlayers(HUMAN);
    } else if (option == '3') {
        clearScreen();
        playTwoPlayers(CPU);
    } else if (option == 27){
        clearScreen();
    }

}

void wait(){ // TODO deberímos poder manejar esto con sleep. De probar paráemtros, esta resultó una buena alternativa
   for (size_t i = 0; i < MS_PER_FRAME; i++) {
   }
}