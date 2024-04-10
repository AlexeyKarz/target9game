/** \file AutoWin.cpp
 *  \brief Implementation file for AutoWin.cpp
 *  Contains the implementation of the functions for auto-solving the game.
 *  \author Aleksei Karzanov
 *  \version 1.0
 *  \date 2024
 */

#include <queue>
#include <set>
#include "../ClassesStack/ClassesStack.h"
#include "AutoWin.h"
#include "../GameFunctions/GameFunctions.h"
#include "GameStateStruct.h"


/** Function <code>copyGrid</code> copies the source grid to the destination grid
 * <BR>
 * @param source the source grid, two-dimensional array 3x3
 * @param destination the destination grid, two-dimensional array 3x3
 */
void copyGrid(int source[GRID_SIZE][GRID_SIZE], int destination[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i)
        for (int j = 0; j < GRID_SIZE; ++j)
            destination[i][j] = source[i][j];
}

/** Function <code>solveGame</code> solves the game by finding the minimum combination of moves.
 * The function uses the Breadth-First Search algorithm to find the solution.
 * <BR>
 * @param grid the initial play field, two-dimensional array 3x3
 * @return Returns a vector of moves that solve the game
 */
vector<Move> solveGameBFS(int grid[GRID_SIZE][GRID_SIZE]) {
    // Define the queue and the visited set
    queue<GameState> q;
    set<GameState> visited;

    GameState initial;
    // Copy the initial grid to the GameState struct and push it to the queue
    copyGrid(grid, initial.grid);
    q.push(initial);

    // Perform the Breadth-First Search
    while (!q.empty()) {
        GameState current = q.front(); q.pop();

        // Check if the current state is a solution and return the moves if it is
        if (victoryCheck(current.grid)) return current.moves;

        // Generate all possible moves from the current state
        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            for (int row = 0; row < GRID_SIZE; ++row) {
                for (int col = 0; col < GRID_SIZE; ++col) {
                    GameState newState = current;
                    Move move;
                    move.row = row;
                    move.col = col;
                    makeMove(newState.grid, move);
                    newState.moves.push_back(Move(row, col));
                    // If the new state is not visited, push it to the queue
                    if (visited.find(newState) == visited.end()) {
                        q.push(newState);
                    }
                }
            }
        }
    }
    return {}; // Return an empty list if no solution is found
}

/**
 * Function <code>calculateCellSum</code> calculates the sum of the values
 * in the same row and column as the cell selected
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @param row the row index
 * @param col the column index
 * @return Returns the sum of the cell values
 */
int calculateCellSum(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    int sum = 0;
    for (int i = 0; i< GRID_SIZE; i++) {
        sum += grid[row][i];
        sum += grid[i][col];
    }
    // subtract the cell value to avoid double counting
    sum -= grid[row][col];
    return sum;
}

/**
 * Function <code>findNextMove</code> finds the next move based on the strategy
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @return Returns the Move class instance, the next move
 */
Move findNextMove(int grid[GRID_SIZE][GRID_SIZE]) {
    int minSum = 9*9; // set to the maximum possible sum
    int cellSum;
    Move nextMove;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cellSum = calculateCellSum(grid, i, j);
            if (cellSum < minSum) {
                minSum = cellSum;
                nextMove.row = i;
                nextMove.col = j;
            }
        }
    }
    return nextMove;
}

/**
 * Function <code>solveGameStrategy</code> solves the game by finding the minimum combination of moves.
 * The function uses the Strategy algorithm to find the solution: The next move is applied to the cell,
 * that has the smallest sum of the values in the row and column.
 * <BR>
 * @param grid the initial play field, two-dimensional array 3x3
 * @return Returns a vector of moves that solve the game
 */
vector<Move> solveGameStrategy(int grid[GRID_SIZE][GRID_SIZE]) {
    vector<Move> solution;
    int tempGrid[GRID_SIZE][GRID_SIZE];
    copyGrid(grid, tempGrid);

    while (!victoryCheck(tempGrid)) {
        Move nextMove = findNextMove(tempGrid);
        solution.push_back(nextMove);
        makeMove(tempGrid, nextMove);
    }
    return solution;
}