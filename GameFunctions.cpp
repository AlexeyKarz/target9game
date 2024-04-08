//
// Created by Karzanov Alexey on 08.04.2024.
//

#include "ClassesStack.h"
#include <iostream>
using namespace std;

/**
 * Function <code>makeMove</code> makes a move on the play field by incrementing the values
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @param move the Move class instance, the move to be made
 */
void makeMove(int grid[GRID_SIZE][GRID_SIZE], const Move move) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == move.row || j == move.col) {
                if (grid[i][j] == 9) {
                    grid[i][j] = 0;
                }
                else {
                    grid[i][j]++;
                }
            }
        }
    }
}

/**
 * Function <code>makeReverseMove</code> makes a reverse move on the play field by decrementing the values
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @param move the Move class instance, the move to be made
 */
void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], const Move move) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == move.row || j == move.col) {
                if (grid[i][j] == 0) {
                    grid[i][j] = 9;
                }
                else {
                    grid[i][j]--;
                }
            }
        }
    }
}

/**
 * Function <code>setDifficulty</code> sets the difficulty level of the game
 * <BR>
 * by making a number of random moves defined by the user's input
 * @param grid the play field, two-dimensional array 3x3
 */
void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]) {
    cout << "Enter the difficulty level (1-9): ";
    int difficulty;
    do {
        cin >> difficulty;
        if (difficulty < 1 || difficulty > 9) {
            cout << "Invalid difficulty level. Please enter a number between 1 and 9: ";
            // clear the input buffer in case the user entered a character
            cin.clear();
            cin.ignore(32767, '\n');
        }
    } while (difficulty < 1 || difficulty > 9);

    srand(time(nullptr));
    for (int i = 0; i < difficulty; i++) {
        // randomize the row and column
        int row = rand() % 3;
        int col = rand() % 3;
        Move move{};
        move.row = row;
        move.col = col;
        // make a "reversed" random move
        makeReverseMove(grid, move);
    }
}


/**
 * Function <code>restartGame</code> restarts the game by resetting all the parameters
 * <BR>
 * @param grid the play field
 * @param history stack that stores moves history
 * @param canceled stack that stores the canceled moves
 */
void restartGame(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 9;
        }
    }
    // set the difficulty level
    setDifficulty(grid);
    // clear the history and canceled moves stacks
    history = StackMoves();
    canceled = StackMoves();
}

/**
 * Function <code>printPlayField</code> prints the play field
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 */
void printPlayField(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Function <code>validateMove</code> checks whether the move is valid
 * <BR>
 * @param cellNum the number of the cell
 * @return Returns <code>true</code> if the move is valid,
 * <code>false</code> otherwise.
*/
bool validateMove(const int cellNum) {
    if (cellNum >= 0 && cellNum <= 2) {
        return true;
    }
    else {
        cout << "Invalid input. Please enter a number between 0 and 2: ";
        return false;
    }
}

/**
 * Function <code>victoryCheck</code> checks whether the user has won the game
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @return Returns <code>true</code> if the user has won the game,
 * <code>false</code> otherwise.
*/
bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != 9) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Function <code>undoMove</code> undoes the last move by making a reverse move taken
 * from the history stack and pushing it to the canceled moves stack
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @param history stack that stores moves history passed by reference
 * @param canceled stack that stores the canceled moves passed by reference
 */
void undoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
    Move move{};
    history.top(move);
    makeReverseMove(grid, move);
    canceled.push(move);
    history.pop();
}

/**
 * Function <code>redoMove</code> redoes the last move by making a move taken
 * from the canceled moves stack and pushing it to the history stack
 * <BR>
 * @param grid the play field, two-dimensional array 3x3
 * @param history stack that stores moves history passed by reference
 * @param canceled stack that stores the canceled moves passed by reference
 */
void redoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
    Move move{};
    canceled.top(move);
    makeMove(grid, move);
    history.push(move);
    canceled.pop();
}