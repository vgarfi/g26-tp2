/**
 * @file eliminatorGame.h
 * @brief Definition of constants, structures, and functions for the Eliminator game.
 */

#include <stdint.h>

#ifndef __ELIMINATOR_GAME_H__
#define __ELIMINATOR_GAME_H__

#define ELIMINATOR_PROCESS  "eliminator"

#define ELIMINATOR_EXEC         1
#define TICKS_PER_FRAME         1
#define MS_PER_FRAME            180000

#define BLOCKED_SPACE           1
#define FREE                    0

#define SNAKE_HEAD_SIZE         8
#define WALL_SIZE               8
#define LETTERS_THICK           8

#define WIDTH                   128
#define HEIGHT                  96

#define ELIMINATOR_FONT_LEVEL   4
#define PIXELS_WIDTH            1024
#define PIXELS_HEIGHT           768

#define CRASHED                 1

#define P1_UP_KEY           sysUpArrowValue()
#define P1_DOWN_KEY         sysDownArrowValue()
#define P1_LEFT_KEY         sysLeftArrowValue()
#define P1_RIGHT_KEY        sysRightArrowValue()

#define P2_UP_KEY           'w'
#define P2_DOWN_KEY         's'
#define P2_LEFT_KEY         'a'
#define P2_RIGHT_KEY        'd'

#define ESC                 27
#define SPACE               ' '
#define ONE_PLAYER          '1'
#define TWO_PLAYERS         '2'
#define COMPUTER            '3'
#define RESET               'r'
#define A_OPTION            'a'
#define B_OPTION            'b'
#define C_OPTION            'c'

/**
 * @enum Direction
 * @brief Enumeration of possible directions for the snake.
 */
enum Direction {UP, DOWN, LEFT, RIGHT};

/**
 * @enum Player
 * @brief Enumeration of player types.
 */
enum Player {CPU, HUMAN};

/**
 * @struct SnakeHead
 * @brief Structure representing the head of the snake.
 */
typedef struct {
    uint8_t x;          /**< X-coordinate of the snake head */
    uint8_t y;          /**< Y-coordinate of the snake head */
    uint32_t color;     /**< Color of the snake head */
} SnakeHead;

/**
 * @brief Starts the Eliminator game.
 */
void eliminatorGame(void);

/**
 * @brief Starts a single-player game.
 */
void playAlone(void);

/**
 * @brief Starts a two-player game.
 *
 * @param player2 The type of the second player (CPU or HUMAN).
 */
void playTwoPlayers(int player2);

/**
 * @brief Cleans the game board.
 */
void cleanBoard(void);

/**
 * @brief Prints the game wall.
 */
void printWall(void);

#endif