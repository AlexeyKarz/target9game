/** \file
 * \brief Tests for the game logic.
 * This file contains the tests for the game logic.
 * \author Aleksei Karzanov
 * \version 1.0
 * \date 2024
 */

#include <gtest/gtest.h>
#include "../src/game_logic.cpp"


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

//TEST(GameTest, TestFindNextMove) {
//    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
//
//}