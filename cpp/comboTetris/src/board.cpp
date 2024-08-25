#include "board.h"
#include <cassert>
#include <iostream>
#include <string.h>

Board::Board(i32 width, i32 height):
    bWidth(width),
    bHeight(height)
{
    board = new BoardElem[bWidth * bHeight];
    reset();;
}

Board::~Board() {
    delete [] board;
}
void Board::reset() {
    memset(board, 0, bWidth * bHeight * sizeof(BoardElem));
}

BoardElem Board::elemAt(i32 h, i32 w) {
    assert(h < bHeight && "x out of bounds");
    assert(w < bWidth && "y out of bounds");
    return board[h * bWidth + w];
}

void Board::setAt(i32 h, i32 w, BoardElem val) {
    assert(h < bHeight && "x out of bounds");
    assert(w < bWidth && "y out of bounds");
    // Consider returning old value if needed
    board[h * bWidth + w] = val;
}

void Board::createTestBoard() {
    // Horizontal blue L
    setAt(0, 0, BoardElem::T_BLUE);
    setAt(0, 1, BoardElem::T_BLUE);
    setAt(0, 2, BoardElem::T_BLUE);
    setAt(1, 0, BoardElem::T_BLUE);

    // Top red O
    setAt(bHeight - 1, 9, BoardElem::T_RED);
    setAt(bHeight - 2, 9, BoardElem::T_RED);
    setAt(bHeight - 1, 10, BoardElem::T_RED);
    setAt(bHeight - 2, 10, BoardElem::T_RED);

    // Mid orange I
    setAt(bHeight - 3, 22, BoardElem::T_ORANGE);
    setAt(bHeight - 4, 22, BoardElem::T_ORANGE);
    setAt(bHeight - 5, 22, BoardElem::T_ORANGE);
    setAt(bHeight - 6, 22, BoardElem::T_ORANGE);

    // bottom green Z
    setAt(1, 30, BoardElem::T_GREEN);
    setAt(1, 31, BoardElem::T_GREEN);
    setAt(0, 31, BoardElem::T_GREEN);
    setAt(0, 32, BoardElem::T_GREEN);
}

void Board::debuBoard() {
    for (i32 i = 0; i < bHeight; ++i) {
        for (i32 j = 0; j < bWidth; ++j) {
            std::cout << (i32) elemAt(i, j) << "  ";
        }
        std::cout << "\n";
    }
}
