//
// Created by Karzanov Alexey on 08.04.2024.
//

#include "ClassesStack.h"
#include <new>
using namespace std;

// Move class constructor
Move::Move() {
    row = 0;
    col = 0;
}

// Move class second constructor that takes row and column as arguments
Move::Move(int r, int c) {
    row = r;
    col = c;
}

// Node class constructor
Node::Node() {
    next = nullptr;
}

// Node class second constructor that takes Move instance and the pointer as arguments
Node::Node(Move newmove, Node *n) {
    move = newmove;
    next = n;
}

// StackMoves constructor
StackMoves::StackMoves() {
    topNode = nullptr;
}

/**
 * Function <code>isEmpty</code> checks whether the stack is empty
 * <BR>
 * @return Returns <code>true</code> if the stack is empty,
 * <code>false</code> otherwise.
*/
bool StackMoves::isEmpty() const {
    return topNode == nullptr;
}

/**
 * Function <code>top</code> stores the top element in the stack into the passed variable
 * <BR>
 * @param move the Move class instance passed by variable
 * @return Returns <code>true</code> if the stack is empty,
 * <code>false</code> otherwise.
*/
errorCode StackMoves::top(Move &move) const {
    if (isEmpty()) {
        return underflow;
    }
    else {
        move = topNode->move;
        return success;
    }
}

/**
 * Function <code>pop</code> deletes the last Move from the stack
 * <BR>
 * @return Returns <code>true</code> if the stack is emtpty,
 * <code>false</code> otherwise.
*/
errorCode StackMoves::pop() {
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

/**
 * Function <code>push</code> pushes a Move into the stack
 * <BR>
 * @param Move the Move class instance passed by variable
 * @return Returns <code>overflow</code> if the stack is full,
 * <code>success</code> otherwise.
*/
errorCode StackMoves::push(const Move &move) {
    Node *temp = new(nothrow) Node(move, topNode);
    if (temp == nullptr) {
        return overflow;
    }
    topNode = temp;
    return success;
}