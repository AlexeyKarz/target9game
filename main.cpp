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
 * \date      03/2024-04/2024
 * \copyright University of Nicosia.
*/

// include the necessary libraries
#include <iostream>
//#include <ctime>
#include <cstdlib>
#include <vector>
//#include <queue>
//#include <set>
//#include <chrono>
#include "ClassesStack.h"
#include "AutoWin.h"
#include "GameFunctions.h"
#include "GameState.cpp"

using namespace std;
//
//// define the grid size
//const int GRID_SIZE = 3;

///**
// * The Move class stores the row and column of the move
// * @author: Aleksei Karzanov
// * @version: 1.1.0
// * @since: 1.0.0
// */
//class Move {
//public:
//    int row, col;
//    Move();
//    Move(int r, int c);
//};
//
//// define the error codes
//enum errorCode {underflow, overflow, success};
//
///**
// * The Node class that allows to connect moves as a linked stack
// * @author: Aleksei Karzanov
// * @version: 1.0.0
// * @since: 1.0.0
// */
//class Node {
//public:
//    Move move{};
//    Node *next;
//    Node();
//    Node(Move newmove, Node *n);
//};
//
///**
// * The StackMoves class that allows to store the moves in a linked stack
// * @author: Aleksei Karzanov
// * @version: 1.0.0
// * @since: 1.0.0
// */
//class StackMoves {
//public:
//    StackMoves();
//    errorCode top(Move &move) const;
//    errorCode pop();
//    errorCode push(const Move &move);
//    bool isEmpty() const;
//private:
//    Node *topNode;
//};
//
///**
// * The GameState struct that stores the current state of the game
// * @author: Aleksei Karzanov
// * @version: 1.0.0
// * @since: 1.1.0
// */
//struct GameState {
//    int grid[GRID_SIZE][GRID_SIZE]{};
//    // vector to store the moves that lead to the current state
//    vector<Move> moves;
//
//    // Custom comparison for GameState to work in a set
//    bool operator<(const GameState& rhs) const {
//        for (int i = 0; i < GRID_SIZE; ++i) {
//            for (int j = 0; j < GRID_SIZE; ++j) {
//                /* Compare the grid values and return true if the current grid is
//                 * less than the right-hand side grid, otherwise return false */
//                if (this->grid[i][j] != rhs.grid[i][j]) return this->grid[i][j] < rhs.grid[i][j];
//            }
//        }
//        // If the grids are equal, return false
//        return false;
//    }
//};
//
//// function prototypes for auto solving the game using BFS
//void copyGrid(int source[GRID_SIZE][GRID_SIZE], int destination[GRID_SIZE][GRID_SIZE]);
//vector<Move> solveGameBFS(int grid[GRID_SIZE][GRID_SIZE]);
//
//// function prototypes for auto solving the game using Strategy
//int calculateCellSum(int grid[GRID_SIZE][GRID_SIZE], int row, int col);
//Move findNextMove(int grid[GRID_SIZE][GRID_SIZE]);
//vector<Move> solveGameStrategy(int grid[GRID_SIZE][GRID_SIZE]);
//
//// function prototypes for the game
//void restartGame(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);
//void printPlayField(int grid[GRID_SIZE][GRID_SIZE]);
//void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]);
//void makeMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
//void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
//bool validateMove(int cellNum);
//bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]);
//void undoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);
//void redoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled);

/**
 * Function <code>main</code> is the entry point of the program
 * <BR>
 * @return 0 if the program executed successfully
 */
int main() {

    // initialize the grid, set all values to 9
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    int choice; // variable to store the user's choice

    // initialize the stack where the moves will be stored
    StackMoves movesHistory;
    // initialize the stack where the cancelled moves will be stored
    StackMoves cancelledMoves;

    // set the difficulty level
    setDifficulty(grid);

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
                }
                else {
                    validMove = validateMove(move.row);
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
                }
                else {
                    validMove = validateMove(move.col);
                }
            } while (!validMove);
            makeMove(grid, move);
            movesHistory.push(move); // store the move in the history stack
            // making the move means that the cancelled moves stack should be cleared
            cancelledMoves = StackMoves();
            // check if the user has won the game and if they did, ask if they want to play again
            if (victoryCheck(grid)) {
                cout << "Congratulations! You have won the game!" << endl;
                char restartChoice;
                cout << "Do you want to play again? (y/n):";
                cin >> restartChoice;
                if (restartChoice == 'y' || restartChoice == 'Y') {
                    restartGame(grid, movesHistory, cancelledMoves);
                }
                else {
                    cout << "Have a good day!";
                    exit(0);
                }
            }
        }
        else if (choice == 2) { // redo the move
            // check if there are any moves to redo
            if (cancelledMoves.isEmpty()) {
                cout << "There are no moves to redo." << endl;
            }
            else {
                redoMove(grid, movesHistory, cancelledMoves);
            }
        }
        else if (choice == 3) { // undo the move
            // check if there are any moves to undo
            if (movesHistory.isEmpty()) {
                cout << "There are no moves to undo." << endl;
            }
            else {
                undoMove(grid, movesHistory, cancelledMoves);
            }
        }
        else if (choice == 4) { // restart the game
            restartGame(grid, movesHistory, cancelledMoves);
        }
        else if (choice == 5) { // solve the game
            cout << "Please wait while the game is being solved..." << endl;
            vector<Move> solution;
            /* Strategy only works if the game is in the initial state
             * (set by the difficulty level) and the history stack is empty */
            if (movesHistory.isEmpty()) {
                // use the strategy heuristic search to solve the game
                solution = solveGameStrategy(grid);

            }
            else {
                /* use exhaustive search (BFS) to solve the game
                 * this method is slow, count time taken to solve the game */
                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                solution = solveGameBFS(grid);
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Time taken to solve the game: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;
            }
            // print minimum number of moves to solve the game
            cout << "Minimum number of moves to solve the game: " << solution.size() << endl;
            cout << "Solution: " << endl;
            for (const Move& move : solution) {
                cout << "Row: " << move.row << ", Column: " << move.col << endl;
                makeMove(grid, move);
                movesHistory.push(move); // store the move in the history stack
                printPlayField(grid);
                cout << "----------------" << endl;
            }
            // making the moves means that the cancelled moves stack should be cleared
            cancelledMoves = StackMoves();
        }
        else if (choice == 6) { // quit the game
            cout << "Have a good day!" << endl;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            // clear the input buffer in case the user entered a character
            cin.clear();
            cin.ignore(32767, '\n');
        }
    } while (choice != 6);

    return 0;
}
//
//// Move class constructor
//Move::Move() {
//    row = 0;
//    col = 0;
//}
//
//// Move class second constructor that takes row and column as arguments
//Move::Move(int r, int c) {
//    row = r;
//    col = c;
//}
//
//// Node class constructor
//Node::Node() {
//    next = nullptr;
//}
//
//// Node class second constructor that takes Move instance and the pointer as arguments
//Node::Node(Move newmove, Node *n) {
//    move = newmove;
//    next = n;
//}
//
//// StackMoves constructor
//StackMoves::StackMoves() {
//    topNode = nullptr;
//}
//
///**
// * Function <code>isEmpty</code> checks whether the stack is empty
// * <BR>
// * @return Returns <code>true</code> if the stack is empty,
// * <code>false</code> otherwise.
//*/
//bool StackMoves::isEmpty() const {
//    return topNode == nullptr;
//}
//
///**
// * Function <code>top</code> stores the top element in the stack into the passed variable
// * <BR>
// * @param move the Move class instance passed by variable
// * @return Returns <code>true</code> if the stack is empty,
// * <code>false</code> otherwise.
//*/
//errorCode StackMoves::top(Move &move) const {
//    if (isEmpty()) {
//        return underflow;
//    }
//    else {
//        move = topNode->move;
//        return success;
//    }
//}
//
///**
// * Function <code>pop</code> deletes the last Move from the stack
// * <BR>
// * @return Returns <code>true</code> if the stack is emtpty,
// * <code>false</code> otherwise.
//*/
//errorCode StackMoves::pop() {
//    if (isEmpty()) {
//        return underflow;
//    }
//    else {
//        Node *temp = topNode;
//        topNode = topNode->next;
//        delete temp;
//        return success;
//    }
//}
//
///**
// * Function <code>push</code> pushes a Move into the stack
// * <BR>
// * @param Move the Move class instance passed by variable
// * @return Returns <code>overflow</code> if the stack is full,
// * <code>success</code> otherwise.
//*/
//errorCode StackMoves::push(const Move &move) {
//    Node *temp = new(nothrow) Node(move, topNode);
//    if (temp == nullptr) {
//        return overflow;
//    }
//    topNode = temp;
//    return success;
//}
//
///**
// * Function <code>restartGame</code> restarts the game by resetting all the parameters
// * <BR>
// * @param grid the play field
// * @param history stack that stores moves history
// * @param canceled stack that stores the canceled moves
// */
//void restartGame(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            grid[i][j] = 9;
//        }
//    }
//    // set the difficulty level
//    setDifficulty(grid);
//    // clear the history and canceled moves stacks
//    history = StackMoves();
//    canceled = StackMoves();
//}
//
///**
// * Function <code>printPlayField</code> prints the play field
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// */
//void printPlayField(int grid[GRID_SIZE][GRID_SIZE]) {
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            cout << grid[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
///**
// * Function <code>setDifficulty</code> sets the difficulty level of the game
// * <BR>
// * by making a number of random moves defined by the user's input
// * @param grid the play field, two-dimensional array 3x3
// */
//void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]) {
//    cout << "Enter the difficulty level (1-9): ";
//    int difficulty;
//    do {
//        cin >> difficulty;
//        if (difficulty < 1 || difficulty > 9) {
//            cout << "Invalid difficulty level. Please enter a number between 1 and 9: ";
//            // clear the input buffer in case the user entered a character
//            cin.clear();
//            cin.ignore(32767, '\n');
//        }
//    } while (difficulty < 1 || difficulty > 9);
//
//    srand(time(nullptr));
//    for (int i = 0; i < difficulty; i++) {
//        // randomize the row and column
//        int row = rand() % 3;
//        int col = rand() % 3;
//        Move move{};
//        move.row = row;
//        move.col = col;
//        // make a "reversed" random move
//        makeReverseMove(grid, move);
//    }
//}
//
///** Function <code>copyGrid</code> copies the source grid to the destination grid
// * <BR>
// * @param source the source grid, two-dimensional array 3x3
// * @param destination the destination grid, two-dimensional array 3x3
// */
//void copyGrid(int source[GRID_SIZE][GRID_SIZE], int destination[GRID_SIZE][GRID_SIZE]) {
//    for (int i = 0; i < GRID_SIZE; ++i)
//        for (int j = 0; j < GRID_SIZE; ++j)
//            destination[i][j] = source[i][j];
//}
//
///**
// * Function <code>makeMove</code> makes a move on the play field by incrementing the values
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @param move the Move class instance, the move to be made
// */
//void makeMove(int grid[GRID_SIZE][GRID_SIZE], const Move move) {
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            if (i == move.row || j == move.col) {
//                if (grid[i][j] == 9) {
//                    grid[i][j] = 0;
//                }
//                else {
//                    grid[i][j]++;
//                }
//            }
//        }
//    }
//}
//
///** Function <code>solveGame</code> solves the game by finding the minimum combination of moves.
// * The function uses the Breadth-First Search algorithm to find the solution.
// * <BR>
// * @param grid the initial play field, two-dimensional array 3x3
// * @return Returns a vector of moves that solve the game
// */
//vector<Move> solveGameBFS(int grid[GRID_SIZE][GRID_SIZE]) {
//    // Define the queue and the visited set
//    queue<GameState> q;
//    set<GameState> visited;
//
//    GameState initial;
//    // Copy the initial grid to the GameState struct and push it to the queue
//    copyGrid(grid, initial.grid);
//    q.push(initial);
//
//    // Perform the Breadth-First Search
//    while (!q.empty()) {
//        GameState current = q.front(); q.pop();
//
//        // Check if the current state is a solution and return the moves if it is
//        if (victoryCheck(current.grid)) return current.moves;
//
//        // Generate all possible moves from the current state
//        if (visited.find(current) == visited.end()) {
//            visited.insert(current);
//            for (int row = 0; row < GRID_SIZE; ++row) {
//                for (int col = 0; col < GRID_SIZE; ++col) {
//                    GameState newState = current;
//                    Move move;
//                    move.row = row;
//                    move.col = col;
//                    makeMove(newState.grid, move);
//                    newState.moves.push_back(Move(row, col));
//                    // If the new state is not visited, push it to the queue
//                    if (visited.find(newState) == visited.end()) {
//                        q.push(newState);
//                    }
//                }
//            }
//        }
//    }
//    return {}; // Return an empty list if no solution is found
//}
//
///**
// * Function <code>calculateCellSum</code> calculates the sum of the values
// * in the same row and column as the cell selected
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @param row the row index
// * @param col the column index
// * @return Returns the sum of the cell values
// */
//int calculateCellSum(int grid[GRID_SIZE][GRID_SIZE], int row, int col) {
//    int sum = 0;
//    for (int i = 0; i< GRID_SIZE; i++) {
//        sum += grid[row][i];
//        sum += grid[i][col];
//    }
//    // subtract the cell value to avoid double counting
//    sum -= grid[row][col];
//    return sum;
//}
//
///**
// * Function <code>findNextMove</code> finds the next move based on the strategy
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @return Returns the Move class instance, the next move
// */
//Move findNextMove(int grid[GRID_SIZE][GRID_SIZE]) {
//    int minSum = 9*9; // set to the maximum possible sum
//    int cellSum;
//    Move nextMove;
//
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            cellSum = calculateCellSum(grid, i, j);
//            if (cellSum < minSum) {
//                minSum = cellSum;
//                nextMove.row = i;
//                nextMove.col = j;
//            }
//        }
//    }
//    return nextMove;
//}
//
///**
// * Function <code>solveGameStrategy</code> solves the game by finding the minimum combination of moves.
// * The function uses the Strategy algorithm to find the solution: The next move is applied to the cell,
// * that has the smallest sum of the values in the row and column.
// * <BR>
// * @param grid the initial play field, two-dimensional array 3x3
// * @return Returns a vector of moves that solve the game
// */
//vector<Move> solveGameStrategy(int grid[GRID_SIZE][GRID_SIZE]) {
//    vector<Move> solution;
//    int tempGrid[GRID_SIZE][GRID_SIZE];
//    copyGrid(grid, tempGrid);
//
//    while (!victoryCheck(tempGrid)) {
//        Move nextMove = findNextMove(tempGrid);
//        solution.push_back(nextMove);
//        makeMove(tempGrid, nextMove);
//    }
//    return solution;
//}
//
///**
// * Function <code>makeReverseMove</code> makes a reverse move on the play field by decrementing the values
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @param move the Move class instance, the move to be made
// */
//void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], const Move move) {
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            if (i == move.row || j == move.col) {
//                if (grid[i][j] == 0) {
//                    grid[i][j] = 9;
//                }
//                else {
//                    grid[i][j]--;
//                }
//            }
//        }
//    }
//
//}
//
///**
// * Function <code>validateMove</code> checks whether the move is valid
// * <BR>
// * @param cellNum the number of the cell
// * @return Returns <code>true</code> if the move is valid,
// * <code>false</code> otherwise.
//*/
//bool validateMove(const int cellNum) {
//    if (cellNum >= 0 && cellNum <= 2) {
//        return true;
//    }
//    else {
//        cout << "Invalid input. Please enter a number between 0 and 2: ";
//        return false;
//    }
//}
//
///**
// * Function <code>victoryCheck</code> checks whether the user has won the game
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @return Returns <code>true</code> if the user has won the game,
// * <code>false</code> otherwise.
//*/
//bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]) {
//    for (int i = 0; i < GRID_SIZE; i++) {
//        for (int j = 0; j < GRID_SIZE; j++) {
//            if (grid[i][j] != 9) {
//                return false;
//                }
//        }
//    }
//    return true;
//}
//
///**
// * Function <code>undoMove</code> undoes the last move by making a reverse move taken
// * from the history stack and pushing it to the canceled moves stack
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @param history stack that stores moves history passed by reference
// * @param canceled stack that stores the canceled moves passed by reference
// */
//void undoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
//    Move move{};
//    history.top(move);
//    makeReverseMove(grid, move);
//    canceled.push(move);
//    history.pop();
//}
//
///**
// * Function <code>redoMove</code> redoes the last move by making a move taken
// * from the canceled moves stack and pushing it to the history stack
// * <BR>
// * @param grid the play field, two-dimensional array 3x3
// * @param history stack that stores moves history passed by reference
// * @param canceled stack that stores the canceled moves passed by reference
// */
//void redoMove(int grid[GRID_SIZE][GRID_SIZE], StackMoves &history, StackMoves &canceled) {
//    Move move{};
//    canceled.top(move);
//    makeMove(grid, move);
//    history.push(move);
//    canceled.pop();
//}