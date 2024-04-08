//
// Created by Karzanov Alexey on 08.04.2024.
//

#include <vector>
#include "ClassesStack.h"
using namespace std;

/**
 * The GameState struct that stores the current state of the game
 * @author: Aleksei Karzanov
 * @version: 1.0.0
 * @since: 1.1.0
 */
struct GameState {
    int grid[GRID_SIZE][GRID_SIZE]{};
    // vector to store the moves that lead to the current state
    vector<Move> moves;

    // Custom comparison for GameState to work in a set
    bool operator<(const GameState& rhs) const {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                /* Compare the grid values and return true if the current grid is
                 * less than the right-hand side grid, otherwise return false */
                if (this->grid[i][j] != rhs.grid[i][j]) return this->grid[i][j] < rhs.grid[i][j];
            }
        }
        // If the grids are equal, return false
        return false;
    }
};