# Target 9 Game

## Overview

The Target 9 Game is a command-line based game developed in C++. The game starts with an initial configuration of digits that is set on the difficulty level selected by the user. The user’s target is to change all of them to 9 in the minimum number of moves. The interaction with the game is done through the menu in the command line, which allows to make moves using row and column indexes, undo and redo moves, start a new game or finish the game.

## Getting Started

### Prerequisites

- A C++ compiler (GCC recommended)
- Basic knowledge of C++ programming

### Installation

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the `main.cpp` file using your C++ compiler.
4. Run the compiled file to start the game.

## Usage

The game starts by asking the user to set the difficulty level. The difficulty level determines the number of random moves made at the beginning of the game. The user can then make moves, undo moves, redo moves, restart the game, or quit the game through the command-line menu.

## Code Structure

The code is structured into several classes and functions:

- `Move` class: Stores the row and column of the move.
- `Node` class: Allows to connect moves as a linked stack.
- `StackMoves` class: Allows to store the moves in a linked stack.
- `restartGame` function: Restarts the game by resetting all the parameters.
- `printPlayField` function: Prints the play field.
- `setDifficulty` function: Sets the difficulty level of the game.
- `makeMove` function: Makes a move on the play field by incrementing the values.
- `makeReverseMove` function: Makes a reverse move on the play field by decrementing the values.
- `validateMove` function: Checks whether the move is valid.
- `victoryCheck` function: Checks whether the user has won the game.
- `undoMove` function: Undoes the last move.
- `redoMove` function: Redoes the last move.

## Contributing

Contributions are welcome. Please open an issue to discuss your idea or submit a pull request.

## License

This project is licensed under the terms of the MIT license.

## Contact

Aleksei Karzanov - [GitHub](https://github.com/AlexeyKarz)

## Acknowledgements

- University of Nicosia