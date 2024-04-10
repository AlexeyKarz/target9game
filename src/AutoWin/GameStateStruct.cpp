/** \file
 *  \brief Implementation file for GameState structure.
 *  Contains the implementation of the GameState structure
 *  that is used for auto-solving the game.
 *  \author Aleksei Karzanov
 *  \version 1.0
 *  \date 2024
 */
#include "GameStateStruct.h"

bool GameState::operator<(const GameState& rhs) const {
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