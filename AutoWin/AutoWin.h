/** \file
 * \brief Header file for AutoWin.cpp
 * This file contains the function prototypes for auto solving the game using BFS and Strategy.
 * \author Aleksei Karzanov
 * \version 1.0
 * \date 2024
 */

#ifndef TARGET9_AUTOWIN_H
#define TARGET9_AUTOWIN_H
#include "../ClassesStack/ClassesStack.h"
#include <vector>

using namespace std;

// function prototypes for auto solving the game using BFS
void copyGrid(int source[GRID_SIZE][GRID_SIZE], int destination[GRID_SIZE][GRID_SIZE]);
vector<Move> solveGameBFS(int grid[GRID_SIZE][GRID_SIZE]);

// function prototypes for auto solving the game using Strategy
int calculateCellSum(int grid[GRID_SIZE][GRID_SIZE], int row, int col);
Move findNextMove(int grid[GRID_SIZE][GRID_SIZE]);
vector<Move> solveGameStrategy(int grid[GRID_SIZE][GRID_SIZE]);


#endif //TARGET9_AUTOWIN_H
