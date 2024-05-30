#include "include/eliminatorGameUtils.h"
#include "include/eliminatorGame.h"
#include "include/colors.h"
#include "include/syscalls.h"

static int shellFontLevel;

void initializeEliminator(void){
    sysclearScreen();
    shellFontLevel = sysgetZoomLevel();
    syssetZoomLevel(ELIMINATOR_FONT_LEVEL);
}

void eliminatorReturn(void) {
    syssetZoomLevel(shellFontLevel);
    sysclearScreen();
    sysshowCursor();
}
void printEliminatorTitle(void) {
    
    int beepParameters[10][2] = {
        {200, 3},  // E
        {800, 2},  // L
        {150, 3},  // I
        {700, 2},  // M
        {220, 3},  // I
        {600, 2},  // N
        {250, 3},   // A
        {500, 2},   // T
        {300, 3},   // O
        {400, 2}    // R
    };
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
        "010\n"
        "010\n"
        "010\n"
        "010\n"
        "010\n",
        // M
        "10001\n"
        "11011\n"
        "10101\n"
        "10001\n"
        "10001\n",
        // I
        "010\n"
        "010\n"
        "010\n"
        "010\n"
        "010\n",
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

    int startX = WIDTH / 2 - (4 + 3) * 10 / 2; // Centra la palabra en la pantalla, 4 = ancho de letra, 3 = espacio entre letras
    int startY = HEIGHT / 2 - 5 / 2;

    for (int l = 0; l <= 9; l++) {
        int increment = /*(l == 2 || l == 4)? l*6 :*/ l*7;
        int x = startX + increment;

        int y = startY;

        syssleep(0, TICKS_PER_FRAME);
        for (int i = 0; letters[l][i] != '\0'; i++) {
            if (letters[l][i] == '1') {
                sysprintSquare(x*LETTERS_THICK, y*LETTERS_THICK, LETTERS_THICK, RED);
            }

            if (letters[l][i] == '\n') {
                x = startX + increment;
                y++;
            } else {
                x++;
            }
        }
    
        sysbeepSound(beepParameters[l][1], beepParameters[l][0]);
    }
}
unsigned char menuOption(void){
    printEliminatorTitle();
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 15, (PIXELS_HEIGHT / 12) / 2 + 5);
    print("Welcome to the Eliminator Game\n");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 11, (PIXELS_HEIGHT / 12) / 2 + 6);
    print("Press 1 to play alone\n");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 16, (PIXELS_HEIGHT / 12) / 2 + 7);
    print("Press 2 to play against a friend\n");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 17, (PIXELS_HEIGHT / 12) / 2 + 8);
    print("Press 3 to play against a computer\n");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 9, (PIXELS_HEIGHT / 12) / 2 + 9);
    print("Press ESC to exit\n");
    unsigned char option = getchar();
    while (option != ONE_PLAYER && option != TWO_PLAYERS && option != COMPUTER && option != ESC) {
        option = getchar();
    }
    return option;
}

void playerDied(int P1Crashed, int P2Crashed, int *scoreP1, int *scoreP2) {
    sysprintRectangle(
        PIXELS_WIDTH / 2 - 140, 
        PIXELS_HEIGHT / 2 - 40, 
        35*WALL_SIZE, 
        10*WALL_SIZE, 
        GREY
    );
    if (P1Crashed == CRASHED && P2Crashed == CRASHED) {
        syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 2, (PIXELS_HEIGHT / 12) / 2 - 3);
        print("DRAW!\n");
    } else if (P1Crashed == CRASHED) {
        syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 7, (PIXELS_HEIGHT / 12) / 2 - 3);
        print("PLAYER 2 WINS!\n");
        (*scoreP2)++;
    } else {
        syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 7, (PIXELS_HEIGHT / 12) / 2 - 3);
        print("PLAYER 1 WINS!\n");
        (*scoreP1)++;
    }

    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 15, (PIXELS_HEIGHT / 12) / 2-1);
    print("P1 SCORE is: ");
    char score[10];
    itoa((*scoreP1), score);
    print(score);
    print(" P2 SCORE is: ");
    itoa((*scoreP2), score);
    print(score);
    
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 10, (PIXELS_HEIGHT / 12) / 2);
    print("\nPress R to restart");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 10, (PIXELS_HEIGHT / 12) / 2+1);
    print("\nPress ESC to exit");    
}

void userDied(int* scoreP1) {
    sysprintRectangle(
        PIXELS_WIDTH / 2 - 80, 
        PIXELS_HEIGHT / 2 - 40, 
        20*WALL_SIZE, 
        10*WALL_SIZE, 
        GREY
    );
    (*scoreP1)++;
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 5, (PIXELS_HEIGHT / 12) / 2 - 2);
    print("YOU DIED!");
    
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 10, (PIXELS_HEIGHT / 12) / 2);
    print("Your DEATHS are: ");
    char score[10];
    itoa((*scoreP1), score);
    print(score);

    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 10, (PIXELS_HEIGHT / 12) / 2+1);
    print("Press R to restart");
    syssetCursorPosition((PIXELS_WIDTH / 8) / 2 - 10, (PIXELS_HEIGHT / 12) / 2+2);
    print("Press ESC to exit");
}


int directionIsHorizontal (int direction) {
    return direction == LEFT || direction == RIGHT;
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

int decideSnakeDirectionCPU(int lastDirectionP2, SnakeHead snakeHeadCPU, char** board) {
    switch (lastDirectionP2) {
        
    case UP: 
        if (board[snakeHeadCPU.x][snakeHeadCPU.y-2] == BLOCKED)
            return LEFT;
        else
            return lastDirectionP2;
        break;
    case DOWN:
        if (board[snakeHeadCPU.x][snakeHeadCPU.y+2] == BLOCKED)
            return RIGHT;
        else
            return lastDirectionP2;
        break;
    case LEFT:
        if (board[snakeHeadCPU.x-2][snakeHeadCPU.y] == BLOCKED)
            return DOWN;
        else
            return lastDirectionP2;
        break;
    case RIGHT:
        if (board[snakeHeadCPU.x+2][snakeHeadCPU.y] == BLOCKED)
            return UP;
        else
            return lastDirectionP2;
        break;
    default:
        return lastDirectionP2;
        break;
    }
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

void wait(void){ 
    for (int i = 0; i < MS_PER_FRAME; i++);
}