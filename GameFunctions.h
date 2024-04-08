//
// Created by Karzanov Alexey on 08.04.2024.
//

#ifndef TARGET9_GAMEFUNCTIONS_H
#define TARGET9_GAMEFUNCTIONS_H
#include "ClassesStack.h"

// function prototypes for the game
void restartGame(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);
void printPlayField(int grid[GRID_SIZE][GRID_SIZE]);
void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]);
void makeMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
bool validateMove(int cellNum);
bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]);
void undoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);
void redoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);


#endif //TARGET9_GAMEFUNCTIONS_H
