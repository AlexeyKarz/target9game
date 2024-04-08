//
// Created by Karzanov Alexey on 08.04.2024.
//

#ifndef TARGET9_CLASSESSTACK_H
#define TARGET9_CLASSESSTACK_H

// define the grid size
const int GRID_SIZE = 3;

// Define the error codes
enum errorCode {underflow, overflow, success};

/**
 * The Move class stores the row and column of the move
 * @author: Aleksei Karzanov
 * @version: 1.1.0
 * @since: 1.0.0
 */
class Move {
public:
    int row, col;
    Move();
    Move(int r, int c);
};

/**
 * The Node class that allows to connect moves as a linked stack
 * @author: Aleksei Karzanov
 * @version: 1.0.0
 * @since: 1.0.0
 */
class Node {
public:
    Move move{};
    Node *next;
    Node();
    Node(Move newmove, Node *n);
};

/**
 * The StackMoves class that allows to store the moves in a linked stack
 * @author: Aleksei Karzanov
 * @version: 1.0.0
 * @since: 1.0.0
 */
class StackMoves {
public:
    StackMoves();
    errorCode top(Move &move) const;
    errorCode pop();
    errorCode push(const Move &move);
    bool isEmpty() const;
private:
    Node *topNode;
};

#endif //TARGET9_CLASSESSTACK_H

