# Target 9 Game

## Overview

The Target 9 Game is a command-line based game developed in C++. The game starts with an initial configuration of digits that is set on the difficulty level selected by the user. The user’s target is to change all of them to 9 in the minimum number of moves (the move suggests choosing a cell so all numbers in cell's column and row will be incremented). The interaction with the game is done through the menu in the command line, which allows to make moves using row and column indexes, undo and redo moves, start a new game, auto-solve it or finish the game. 

## File Structure

The program consists of two main files:

- `src/main.cpp`: This is the main file of the program where the game logic is implemented.
- `tests/game_test.cpp`: This file contains the unit tests for the game logic.

## Main Components

### Main Game Loop

The main game loop is where the user interacts with the game. The user is presented with a menu of options to choose from. These options include making a move, undoing a move, redoing a move, restarting the game, solving the game, and quitting the game.

### Move Validation

Before a move is made, it is validated to ensure it is within the acceptable range. If the move is not valid, the user is prompted to enter a valid move.

### Game Solving

The game can be solved automatically using two different strategies. If the game is in its initial state, a heuristic search strategy is used. If the game is not in its initial state, an exhaustive search strategy (BFS) is used.

### Undo and Redo

The program keeps a history of moves made by the user. This allows the user to undo and redo moves. When a move is undone, it is stored in a separate stack of cancelled moves. When a move is redone, it is moved back to the history stack.

### Victory Check

After each move, the program checks if the user has won the game. If the user has won, they are congratulated and asked if they want to play again.

## Testing

The program includes a suite of unit tests to ensure the game logic is working correctly. These tests cover the game solving algorithm, the undo and redo functionality, the victory check, and the game restart functionality.

## Logging
The "Target 9" game uses the spdlog library for logging. The logger is set up in the `setup_logger()` function, which creates a rotating file sink. This sink is configured to create a new log file once the current one reaches 5MB in size, and it keeps the last 3 log files.  The logger is used throughout the game to log various events. **These include: The start and end of the game , User moves, Invalid inputs, Game restarts.**

The initial state of the game and any changes to the game state
The logger is set to the debug level, meaning it will log all messages with a severity of debug or higher. This includes info, warning, error, and critical messages. The log files are stored in the `../cmake-build-debug/logs/game.log` directory.  To view the logs, open the log files in any text editor.

## Running the Program

To run the program, compile the `src/main.cpp` file and execute the resulting binary. To run the tests, compile the `tests/game_test.cpp` file and execute the resulting binary.

## Conclusion

This game program is a fun and challenging puzzle game. It includes a variety of features to enhance the user experience, including move validation, automatic game solving, undo and redo functionality, and a victory check. The program is thoroughly tested to ensure the game logic is working correctly.

## Contributing

Contributions are welcome. Please open an issue to discuss your idea or submit a pull request.

## License

This project is licensed under the terms of the MIT license.

## Contact

Aleksei Karzanov - [GitHub](https://github.com/AlexeyKarz)

## Acknowledgements

- The game was created by Dr Andreas Savva, the professor in the University of Nicosia.
