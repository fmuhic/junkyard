#pragma once

#pragma once

#include "raylib.h"
#include "board.h"

struct Renderer {
    Renderer();

    void draw(Camera2D &camera, Board& board);

    private:

    void drawWiredBoard(Board& board);
    void drawBoardCells(Board& board);
    Color pickCellColor(BoardElem elem);
};

