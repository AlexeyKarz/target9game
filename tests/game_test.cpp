/** \file
 * \brief Tests for the game logic.
 * This file contains the tests for the game logic.
 * \author Aleksei Karzanov
 * \version 1.0
 * \date 2024
 */

#include <gtest/gtest.h>
#include "../src/game_logic.cpp"
#include <sstream>


TEST(GameTest, TestBFSAutoSolve) {
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    // set random difficulty 1 - 9
    srand(time(nullptr));
    int diff = rand() % 9 + 1;

    // make random reverse moves
    for (int i = 0; i < diff; i++) {
        Move move = initializeRandomMove();
        makeReverseMove(grid, move);
    }

    /* The following code makes random moves to the grid, but it is
     * commented out because (even though it works) the BFS algorithm
     * has very high time complexity and is used only if the history of
     * moves is not empty. After making close to 10 random moves the solving algorithm
     * can take up to several minutes to solve the game. Uncomment the following
     * code to test the game with random moves made. */
    // reset the number of moves and  make random moves
//    diff = rand() % 9 + 1;
//    for (int i = 0; i < diff; i++) {
//        Move move = initializeRandomMove();
//        makeMove(grid, move);
//    }

    // solve the game
    vector<Move> solution;
    solution = solveGameBFS(grid);
    for (const Move& move : solution) {
        makeMove(grid, move);
    }
    // check if the game is solved
    ASSERT_TRUE(victoryCheck(grid));
}

TEST(GameTest, PrintPlayField) {
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    printPlayField(grid);
}

TEST(GameTest, TestUndoRedo) {
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    StackMoves history;
    StackMoves canceled;

    // set random difficulty 1 - 9
    srand(time(nullptr));
    int diff = rand() % 9 + 1;

    // make random reverse moves
    for (int i = 0; i < diff; i++) {
        Move move = initializeRandomMove();
        makeReverseMove(grid, move);
    }

    // make random moves
    diff = rand() % 9 + 1;
    for (int i = 0; i < diff; i++) {
        Move move = initializeRandomMove();
        makeMove(grid, move);
    }

    // copy the grid
    int gridCopy[GRID_SIZE][GRID_SIZE];
    copyGrid(grid, gridCopy);

    // undo the moves
    for (int i = 0; i < diff; i++) {
        undoMove(grid, history, canceled);
    }

    // redo the moves
    for (int i = 0; i < diff; i++) {
        redoMove(grid, history, canceled);
    }

    // check if the grid is the same as the copy
    bool same = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != gridCopy[i][j]) {
                same = false;
                break;
            }
        }
    }
    ASSERT_TRUE(same);
}

TEST(GameTest, TestFindNextMove) {
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    // set random difficulty 1 - 9
    srand(time(nullptr));
    int diff = rand() % 9 + 1;

    // make random reverse moves
    for (int i = 0; i < diff; i++) {
        Move move = initializeRandomMove();
        makeReverseMove(grid, move);
    }

    // solve the game
    vector<Move> solution;
    solution = solveGameStrategy(grid);
    for (const Move& move : solution) {
        makeMove(grid, move);
    }
    // check if the game is solved
    ASSERT_TRUE(victoryCheck(grid));

}

TEST(GameTest, RestartGame) {
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    StackMoves history;
    StackMoves canceled;

    // set random number of moves 1 - 9
    srand(time(nullptr));
    int diff = rand() % 9 + 1;

    // add random moves to the history and cancelled stack
    for (int i = 0; i < diff; i++) {
        Move move = initializeRandomMove();
        history.push(move);
        canceled.push(move);
    }

    // Simulate user input (difficulty level)
    ostringstream formattedInput;
    formattedInput << diff << "\n";

    // redirect cin to the input string
    istringstream input(formattedInput.str());
    cin.rdbuf(input.rdbuf());
    cin.rdbuf(input.rdbuf());

    // restart the game
    restartGame(grid, history, canceled);

    /* If the game is restarted correctly, at least some
     * of the cells will not be set to '9" and stacks will
     * be empty. */

    // check if the grid is not set to '9'
    int nineCount = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 9) {
                nineCount++;
            }
        }
    }
    bool reset = nineCount < 9;

    // check if the history and canceled stacks are empty
    reset = reset && history.isEmpty();
    reset = reset && canceled.isEmpty();

    ASSERT_TRUE(reset);
}
