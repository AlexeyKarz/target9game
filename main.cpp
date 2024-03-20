#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// define the grid size
const int GRID_SIZE = 3;

// define the Move class
class Move {
public:
    int row, col;
};

// define the error codes
enum errorCode {underflow, overflow, success};

// define the Node class
class Node {
public:
    Move move{};
    Node *next;
    Node();
    Node(Move newmove, Node *n);
};

Node::Node() {
    next = nullptr;
}

Node::Node(Move newmove, Node *n) {
    move = newmove;
    next = n;
}

// define the class to store the moves
class stackMoves {
public:
    stackMoves();
    errorCode top(Move &move) const;
    errorCode pop();
    errorCode push(const Move &move);
    bool isEmpty() const;
    int getSize() const;
private:
    Node *topNode;
};

// function prototypes
void restartGame(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled);
void printPlayField(int grid[GRID_SIZE][GRID_SIZE]);
void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]);
void makeMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
void validateMove(int cellNum);
bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]);
void undoMove(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled);
void redoMove(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled);

int main() {

    // initialize the grid, set all values to 9
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    int choice; // variable to store the user's choice

    // initialize the stack where the moves will be stored
    stackMoves movesHistory;
    // initialize the stack where the cancelled moves will be stored
    stackMoves cancelledMoves;

    // set the difficulty level
    setDifficulty(grid);

    // print the menu
    do {
        cout << "The play field: " << endl;
        printPlayField(grid);

        cout << "\n1) Make a move";
        cout << "\n2) Redo the move";
        cout << "\n3) Undo the move";
        cout << "\n4) Restart the game";
        cout << "\n5) Quit the game.";
        cout << "\nEnter the choice: ";
        cin >> choice;

        if (choice == 1) {
            Move move{};
            cout << "Enter the row (0-2): ";
            do {
                cin >> move.row;
                validateMove(move.row);
            } while (move.row < 0 || move.row > 2);
            cout << "Enter the column (0-2): ";
            do {
                cin >> move.col;
                validateMove(move.col);
            } while (move.col < 0 || move.col > 2);
            makeMove(grid, move);
            movesHistory.push(move); // store the move in the history stack
            cancelledMoves = stackMoves(); // clear the cancelled moves stack after a new move
            // check if the user has won the game and ask if they want to play again
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
        else if (choice == 2) {
            if (cancelledMoves.isEmpty()) {
                cout << "There are no moves to redo." << endl;
            }
            else {
                redoMove(grid, movesHistory, cancelledMoves);
            }
        }
        else if (choice == 3) {
            if (movesHistory.isEmpty()) {
                cout << "There are no moves to undo." << endl;
            }
            else {
                undoMove(grid, movesHistory, cancelledMoves);
            }
        }


        else if (choice == 4) {
            // Restart the game
            restartGame(grid, movesHistory, cancelledMoves);
        }
    } while (choice != 5);


    return 0;
}

// Node class methods implementation
stackMoves::stackMoves() {
    topNode = nullptr;
}

bool stackMoves::isEmpty() const {
    return topNode == nullptr;
}

errorCode stackMoves::top(Move &move) const {
    if (isEmpty()) {
        return underflow;
    }
    else {
        move = topNode->move;
        return success;
    }
}

errorCode stackMoves::pop() {
    if (isEmpty()) {
        return underflow;
    }
    else {
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
        return success;
    }
}

errorCode stackMoves::push(const Move &move) {
    Node *temp = new(nothrow) Node(move, topNode);
    if (temp == nullptr) {
        return overflow;
    }
    topNode = temp;
    return success;
}

int stackMoves::getSize() const {
    int count = 0;
    Node *temp = topNode;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void restartGame(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 9;
        }
    }
    setDifficulty(grid);
    history = stackMoves();
    canceled = stackMoves();
}

void printPlayField(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void setDifficulty(int grid[GRID_SIZE][GRID_SIZE]) {
    cout << "Enter the difficulty level (1-9): ";
    int difficulty;
    do {
        cin >> difficulty;
        if (difficulty < 1 || difficulty > 9) {
            cout << "Invalid difficulty level. Please enter a number between 1 and 9: ";
        }
    } while (difficulty < 1 || difficulty > 9);

    srand(time(nullptr));
    for (int i = 0; i < difficulty; i++) {
        int row = rand() % 3;
        int col = rand() % 3;
        Move move{};
        move.row = row;
        move.col = col;
        makeReverseMove(grid, move);
    }
}

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

void validateMove(const int cellNum) {
    if (cellNum < 0 || cellNum > 2) {
        cout << "Invalid cell number. Please enter a number between 0 and 2: ";
    }
}

bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]) {
    bool win = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != 9) {
                win = false;
                break;
                }
        }
    }
    return win;
}

void undoMove(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled) {
    Move move{};
    history.top(move);
    makeReverseMove(grid, move);
    canceled.push(move);
    history.pop();
}

void redoMove(int grid[GRID_SIZE][GRID_SIZE], stackMoves &history, stackMoves &canceled) {
    Move move{};
    canceled.top(move);
    makeMove(grid, move);
    history.push(move);
    canceled.pop();
}
