#include "include/eliminatorGameUtils.h"
#include "include/eliminatorGame.h"
#include "include/colors.h"
#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/string.h"
#include "include/utils.h"

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

    int startX = WIDTH / 2 - (4 + 3) * 10 / 2;
    int startY = HEIGHT / 2 - 10;

    for (int l = 0; l < 10; l++) {
        int increment = l*7;
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
unsigned char menuOption(int* map){
    printEliminatorTitle();
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 15, (PIXELS_HEIGHT / 22) / 2);
    print("Welcome to the Eliminator Game\n");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 11, (PIXELS_HEIGHT / 22) / 2 + 1);
    print("Press 1 to play alone\n");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 16, (PIXELS_HEIGHT / 22) / 2 + 2);
    print("Press 2 to play against a friend\n");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 17, (PIXELS_HEIGHT / 22) / 2 + 3);
    print("Press 3 to play against a computer\n");
    
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 27, (PIXELS_HEIGHT / 22) / 2 + 10);
    print("Change maps by pressing A [BASIC], B [MEDIUM], C [HARD] \n");
    
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 9, (PIXELS_HEIGHT / 22) / 2 + 9);
    print("Press ESC to exit\n");
    sysclearKbEntry();
    unsigned char option = getchar();

    while (option != ONE_PLAYER && option != TWO_PLAYERS && option != COMPUTER && option != ESC) {
        option = getchar();
        if (option == A_OPTION || option == B_OPTION || option == C_OPTION) {
            sysbeepSound(1, DO_PRIMA);
            sysbeepSound(2, SI);
            // TODO mostrar un texto que dps se borre (rectangulazo negro) que diga MAP X SELECTED
            switch (option) {
                case A_OPTION:
                    *map = MAP_A;
                    break;
                case B_OPTION:
                    *map = MAP_B;
                    break;
                case C_OPTION:
                    *map = MAP_C;
                    break;
            }
        }
        
    }
    return option;
}

void playerDied(int P1Crashed, int P2Crashed, int *scoreP1, int *scoreP2) {
    sysprintRectangle(
        PIXELS_WIDTH / 2 - 200, 
        PIXELS_HEIGHT / 2 - 60, 
        48*WALL_SIZE, 
        22*WALL_SIZE, 
        GREY
    );
    if (P1Crashed == CRASHED && P2Crashed == CRASHED) {
        syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 2, (PIXELS_HEIGHT / 22) / 2 - 3);
        print("DRAW!");
    } else if (P1Crashed == CRASHED) {
        syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 7, (PIXELS_HEIGHT / 22) / 2 - 3);
        print("PLAYER 2 WINS!");
        (*scoreP2)++;
    } else {
        syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 7, (PIXELS_HEIGHT / 22) / 2 - 3);
        print("PLAYER 1 WINS!");
        (*scoreP1)++;
    }

    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 15, (PIXELS_HEIGHT / 22) / 2 - 1);
    print("P1 SCORE is: ");
    char score[10];
    itoa((*scoreP1), score);
    print(score);
    print(" P2 SCORE is: ");
    itoa((*scoreP2), score);
    print(score);
    
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 -9, (PIXELS_HEIGHT / 22) / 2);
    print("Press R to restart");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 8, (PIXELS_HEIGHT / 22) / 2+1);
    print("Press ESC to exit");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 11, (PIXELS_HEIGHT / 22) / 2+2);
    print("Press SPACE to replay");
}

void twoPlayersSound(int didP1Crashed, int didP2Crashed, int player2) {
    if (didP1Crashed == CRASHED && didP2Crashed != CRASHED) {
        if (player2 == CPU) {
            sysbeepSound(3, DO_PRIMA);
            sysbeepSound(2, SI);
            sysbeepSound(1, LA);
            sysbeepSound(1, SOL);
            sysbeepSound(1, FA);
        } else {
            sysbeepSound(3, DO);
            sysbeepSound(2, RE);
            sysbeepSound(1, MI);
            sysbeepSound(1, FA);
            sysbeepSound(1, SOL);
            sysbeepSound(1, LA);
            sysbeepSound(1, SI);
            sysbeepSound(1, DO_PRIMA);
        }
    } else if (didP1Crashed != CRASHED && didP2Crashed == CRASHED) {
        if (player2 == CPU) {
            sysbeepSound(3, DO_PRIMA);
            sysbeepSound(2, SI);
            sysbeepSound(1, LA);
            sysbeepSound(1, SOL);
            sysbeepSound(1, FA);
        } else {
            sysbeepSound(3, DO);
            sysbeepSound(2, RE);
            sysbeepSound(1, MI);
            sysbeepSound(1, FA);
            sysbeepSound(1, SOL);
            sysbeepSound(1, LA);
            sysbeepSound(1, SI);
            sysbeepSound(1, DO_PRIMA);
        }
    }
}

void userDied(int* scoreP1) {
    sysprintRectangle(
        PIXELS_WIDTH / 2 - 190, 
        PIXELS_HEIGHT / 2 - 60, 
        44*WALL_SIZE, 
        22*WALL_SIZE, 
        GREY
    );
    (*scoreP1)++;
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 5, (PIXELS_HEIGHT / 22) / 2 - 3);
    print("YOU DIED!");
    
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 10, (PIXELS_HEIGHT / 22) / 2 - 1);
    print("Your DEATHS are: ");
    char score[10];
    itoa((*scoreP1), score);
    print(score);

    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 14, (PIXELS_HEIGHT / 22) / 2);
    print("Press R to restart scores");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 10, (PIXELS_HEIGHT / 22) / 2+1);
    print("Press ESC to exit");
    syssetCursorPosition((PIXELS_WIDTH / 12) / 2 - 12, (PIXELS_HEIGHT / 22) / 2+2);
    print("Press SPACE to replay");
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

int decideSnakeDirectionCPU(int lastDirectionP2, SnakeHead snakeHeadCPU, char board[WIDTH][HEIGHT]) {
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