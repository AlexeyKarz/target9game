/**
 * \file main.cpp
 * \title Target 9 Game
 * \brief The program contains the source code for the "Target 9" Game.
 * \details The game starts with an initial configuration of digits that is set on
 * the difficulty level selected by the user and the user’s target is to change all of them
 * to 9 in the minimum number of moves. The interaction with the game is done through the menu
 * in the command line, which allows to make moves using row and column indexes. undo and redo moves,
 * start a new game or finish the game.
 * \author Aleksei Karzanov
 * \version   1.1.0
 * \date      03/2024-05/2024
 * \copyright University of Nicosia. The game was created by Dr Andreas Savva
*/

// include the necessary libraries
#include <iostream>
#include <cstdlib>
#include <vector>]
#include "game_logic.cpp"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace std;


// initialize the logger with rotating file sink
shared_ptr<spdlog::logger> setup_logger() {
    try {
        // Rotating file sink: 5MB size max, 3 rotated files kept
        auto file_sink = make_shared<spdlog::sinks::rotating_file_sink_mt>("../logs/game.log", 1048576 * 5, 3);
        file_sink->set_level(spdlog::level::debug);

        auto logger = make_shared<spdlog::logger>("game_logger", file_sink);
        logger->set_level(spdlog::level::debug);
        spdlog::register_logger(logger);
        return logger;
    } catch (const spdlog::spdlog_ex& ex) {
        cerr << "Logging initialization failed: " << ex.what() << std::endl;
        return nullptr;
    }
}




/**
 * Function <code>main</code> is the entry point of the program
 * <BR>
 * @return 0 if the program executed successfully
 */
int main() {

    // set up the logger
    auto logger = setup_logger();

    if (logger) {
        logger->info("The game has started.");


        // initialize the grid, set all values to 9
        int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

        int choice; // variable to store the user's choice

        // initialize the stack where the moves will be stored
        StackMoves movesHistory;
        // initialize the stack where the cancelled moves will be stored
        StackMoves cancelledMoves;

        // set the difficulty level
        setDifficulty(grid);

        // log the initial state of the game
        logger->info("The game has started with the following play field: Row0: {}, {}, {}, Row:1 {}, {}, {}, Row:2 {}, {}, {}",
                     grid[0][0], grid[0][1], grid[0][2], grid[1][0], grid[1][1], grid[1][2], grid[2][0], grid[2][1], grid[2][2]);


        // print the play field and the menu
        do {
            cout << "The play field: " << endl;
            printPlayField(grid);

            cout << "\n1) Make a move";
            cout << "\n2) Redo the move";
            cout << "\n3) Undo the move";
            cout << "\n4) Restart the game";
            cout << "\n5) Solve the game.";
            cout << "\n6) Exit the game.";
            cout << "\nEnter the choice: ";
            cin >> choice;

            if (choice == 1) { // make a move
                Move move{};
                bool validMove = false; // variable to store the move validation
                // ask the user to enter the row and column
                cout << "Enter the row (0-2): ";
                do {
                    cin >> move.row;
                    if (!cin) { // check if the user entered a character
                        cin.clear();
                        cin.ignore(32767, '\n');
                        cout << "Invalid input. Please enter a number between 0 and 2: ";
                    } else {
                        validMove = validateMove(move.row);
                        if (!validMove) {
                            logger->warn("The user has entered an invalid row number: {}", move.row);
                        }
                    }
                } while (!validMove);
                cout << "Enter the column (0-2): ";
                validMove = false; // reset the variable
                do {
                    cin >> move.col;
                    if (!cin) { // check if the user entered a character
                        cin.clear();
                        cin.ignore(32767, '\n');
                        cout << "Invalid input. Please enter a number between 0 and 2: ";
                    } else {
                        validMove = validateMove(move.col);
                        if (!validMove) {
                            logger->warn("The user has entered an invalid row number: {}", move.row);
                        }
                    }
                } while (!validMove);

                logger->info("The user has made a move: row {}, column {}", move.row, move.col);

                makeMove(grid, move);
                movesHistory.push(move); // store the move in the history stack
                // making the move means that the cancelled moves stack should be cleared
                cancelledMoves = StackMoves();
                // check if the user has won the game and if they did, ask if they want to play again
                if (victoryCheck(grid)) {
                    cout << "Congratulations! You have won the game!" << endl;

                    logger->info("The user has won the game.");

                    char restartChoice;
                    cout << "Do you want to play again? (y/n):";
                    cin >> restartChoice;
                    if (restartChoice == 'y' || restartChoice == 'Y') {
                        restartGame(grid, movesHistory, cancelledMoves);
                        logger->info("The user has restarted the game.");
                        logger->info("The game has started with the following play field: Row0: {}, {}, {}, Row:1 {}, {}, {}, Row:2 {}, {}, {}",
                                     grid[0][0], grid[0][1], grid[0][2], grid[1][0], grid[1][1], grid[1][2], grid[2][0], grid[2][1], grid[2][2]);
                    } else {
                        cout << "Have a good day!";
                        logger-> info("The game has ended.");
                        exit(0);
                    }
                }
            } else if (choice == 2) { // redo the move
                // check if there are any moves to redo
                if (cancelledMoves.isEmpty()) {
                    cout << "There are no moves to redo." << endl;
                } else {
                    redoMove(grid, movesHistory, cancelledMoves);
                    logger->info("The user has redone the move.");
                }
            } else if (choice == 3) { // undo the move
                // check if there are any moves to undo
                if (movesHistory.isEmpty()) {
                    cout << "There are no moves to undo." << endl;
                } else {
                    undoMove(grid, movesHistory, cancelledMoves);
                    logger->info("The user has undone the move.");
                }
            } else if (choice == 4) { // restart the game
                restartGame(grid, movesHistory, cancelledMoves);
                logger->info("The user has restarted the game.");
                logger->info("The game has started with the following play field: Row0: {}, {}, {}, Row:1 {}, {}, {}, Row:2 {}, {}, {}",
                             grid[0][0], grid[0][1], grid[0][2], grid[1][0], grid[1][1], grid[1][2], grid[2][0], grid[2][1], grid[2][2]);
            } else if (choice == 5) { // solve the game
                cout << "Please wait while the game is being solved..." << endl;
                vector<Move> solution;
                /* Strategy only works if the game is in the initial state
                 * (set by the difficulty level) and the history stack is empty */
                if (movesHistory.isEmpty()) {
                    // use the strategy heuristic search to solve the game
                    solution = solveGameStrategy(grid);
                    logger->info("The game has been solved using the strategy algorithm.");

                } else {
                    /* use exhaustive search (BFS) to solve the game
                     * this method is slow, count time taken to solve the game */
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                    solution = solveGameBFS(grid);
                    chrono::steady_clock::time_point end = chrono::steady_clock::now();
                    logger->info("The game has been solved using the BFS algorithm.");
                    cout << "Time taken to solve the game: "
                         << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
                }
                // print minimum number of moves to solve the game
                cout << "Minimum number of moves to solve the game: " << solution.size() << endl;
                logger->info("The game has been solved in {} moves.", solution.size());
                cout << "Solution: " << endl;
                for (const Move &move: solution) {
                    cout << "Row: " << move.row << ", Column: " << move.col << endl;
                    makeMove(grid, move);
                    movesHistory.push(move); // store the move in the history stack
                    printPlayField(grid);
                    cout << "----------------" << endl;
                }
                // making the moves means that the cancelled moves stack should be cleared
                cancelledMoves = StackMoves();
            } else if (choice == 6) { // quit the game
                cout << "Have a good day!" << endl;
                logger->info("The game has ended.");
            } else {
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                // clear the input buffer in case the user entered a character
                cin.clear();
                cin.ignore(32767, '\n');
            }
        } while (choice != 6);

    } // end of if (logger)
    return 0;
}

