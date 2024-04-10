/** \file
 *  \brief Declaration file for GameState structure.
 *  \author Aleksei Karzanov
 *  \version 1.0
 *  \date 2024
 */

#ifndef TARGET9GAME_GAMESTATESTRUCT_H
#define TARGET9GAME_GAMESTATESTRUCT_H
#include <vector>
#include "../ClassesStack/ClassesStack.h"
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
    bool operator<(const GameState& rhs) const;
};


#endif //TARGET9GAME_GAMESTATESTRUCT_H
