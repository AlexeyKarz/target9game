//
// Created by Karzanov Alexey on 08.04.2024.
//

#ifndef TARGET9_AUTOWIN_H
#define TARGET9_AUTOWIN_H
#include "ClassesStack.h"
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
