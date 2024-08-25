#pragma once

#include "types.h"

enum class BoardElem: i32 {
    T_EMPTY = 0,
    T_BLUE,
    T_RED,
    T_ORANGE,
    T_GREEN,
};

class Board {
    public:
    Board(i32 width, i32 height);
    ~Board();

    BoardElem elemAt(i32 h, i32 w);
    void setAt(i32 h, i32 w, BoardElem val);
    void createTestBoard();
    void reset();

    i32 inline width() { return bWidth; }
    i32 inline height() { return bHeight; }
    void debuBoard();

    private:

    i32 bWidth;
    i32 bHeight;
    BoardElem *board;
};
