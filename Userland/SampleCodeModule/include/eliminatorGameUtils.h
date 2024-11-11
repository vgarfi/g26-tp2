/**
 * @file eliminatorGameUtils.h
 * @brief Definition of utility functions and constants for the Eliminator game.
 */

#include "eliminatorGame.h"

#ifndef __ELIMINATOR_GAME__UTILS_H__
#define __ELIMINATOR_GAME_UTILS_H__

#define DEBOUNCER   3200

#define MAP_A       0
#define MAP_B       1
#define MAP_C       2

/**
 * @brief Initializes the Eliminator game.
 */
void initializeEliminator(void);

/**
 * @brief Prints the title of the Eliminator game.
 */
void printEliminatorTitle(void);

/**
 * @brief Displays the menu and gets the selected option.
 *
 * @param map Pointer to store the selected map.
 * @return The selected menu option.
 */
unsigned char menuOption(int* map);

/**
 * @brief Handles the event when a player dies.
 *
 * @param P1Crashed Indicates if player 1 crashed.
 * @param P2Crashed Indicates if player 2 crashed.
 * @param scoreP1 Pointer to the score of player 1.
 * @param scoreP2 Pointer to the score of player 2.
 */
void playerDied(int P1Crashed, int P2Crashed, int *scoreP1, int *scoreP2);

/**
 * @brief Handles the event when the user dies.
 *
 * @param scoreP1 Pointer to the score of player 1.
 */
void userDied(int* scoreP1);

/**
 * @brief Plays the sound for a two-player game.
 *
 * @param P1Crashed Indicates if player 1 crashed.
 * @param P2Crashed Indicates if player 2 crashed.
 * @param player2 The type of the second player (CPU or HUMAN).
 */
void twoPlayersSound(int P1Crashed, int P2Crashed, int player2);

/**
 * @brief Waits for a specified duration.
 */
void wait(void);

/**
 * @brief Checks if the direction is horizontal.
 *
 * @param direction The direction to check.
 * @return 1 if the direction is horizontal, 0 otherwise.
 */
int directionIsHorizontal(int direction);

/**
 * @brief Decides the direction of the snake based on user input.
 *
 * @param lastDirection The last direction of the snake.
 * @param sys_up_arrow_value The value of the up arrow key.
 * @param sys_down_arrow_value The value of the down arrow key.
 * @param sys_left_arrow_value The value of the left arrow key.
 * @param sys_right_arrow_value The value of the right arrow key.
 * @param keyPressed The key pressed by the user.
 * @return The new direction of the snake.
 */
int decideSnakeDirection(int lastDirection, int sys_up_arrow_value, int sys_down_arrow_value, int sys_left_arrow_value, int sys_right_arrow_value, unsigned char keyPressed);

/**
 * @brief Decides the direction of the snake controlled by the CPU.
 *
 * @param lastDirectionP2 The last direction of the CPU-controlled snake.
 * @param snakeHeadCPU The head of the CPU-controlled snake.
 * @param board The game board.
 * @return The new direction of the CPU-controlled snake.
 */
int decideSnakeDirectionCPU(int lastDirectionP2, SnakeHead snakeHeadCPU, char board[WIDTH][HEIGHT]);

/**
 * @brief Updates the position of the snake head based on the direction.
 *
 * @param head Pointer to the snake head.
 * @param direction The direction to move the snake head.
 */
void updateSnakeHead(SnakeHead *head, int direction);

/**
 * @brief Returns to the main menu of the Eliminator game.
 */
void eliminatorReturn(void);

#endif