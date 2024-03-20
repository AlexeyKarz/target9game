#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// define the grid size
const int GRID_SIZE = 3;

class Move {
public:
    int row, col;
};

void printPlayField(int grid[GRID_SIZE][GRID_SIZE]);
void setDifficulty(int level, int grid[GRID_SIZE][GRID_SIZE]);
void makeMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
void makeReverseMove(int grid[GRID_SIZE][GRID_SIZE], Move move);
void validateMove(int cellNum);
bool victoryCheck(const int grid[GRID_SIZE][GRID_SIZE]);


int main() {

    // initialize the grid, set all values to 9
    int grid[GRID_SIZE][GRID_SIZE] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    int choice;

    // set the difficulty level
    cout << "Enter the difficulty level (1-9): ";
    int difficulty;
    do {
        cin >> difficulty;
        if (difficulty < 1 || difficulty > 9) {
            cout << "Invalid difficulty level. Please enter a number between 1 and 9: ";
        }
    } while (difficulty < 1 || difficulty > 9);
    setDifficulty(difficulty, grid);

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
        }
        else if (choice == 4) {
            main();
        }
    } while (choice != 5);


    return 0;
}

void printPlayField(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void setDifficulty(const int level, int grid[GRID_SIZE][GRID_SIZE]) {
    srand(time(nullptr));
    for (int i = 0; i < level; i++) {
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
    if (victoryCheck(grid)) {
        cout << "Congratulations! You have won the game!" << endl;
        char choice;
        cout << "Do you want to play again? (y/n):";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            main();
        }
        else {
            cout << "Goodbye!";
            exit(0);
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