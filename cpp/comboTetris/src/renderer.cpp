#include "renderer.h"
#include "types.h"
#include "board.h"
#include "raylib.h"
#include <cmath>

Renderer::Renderer() {
}

void Renderer::draw(Camera2D& camera, Board& board) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    
        drawBoardCells(board);
        drawWiredBoard(board);

    EndMode2D();
    EndDrawing();
}

void Renderer::drawBoardCells(Board& board) {
    f32 angle = 2.0f * PI / board.width();
    f32 r = 2.3f;
    for (i32 j = 0; j < board.height(); ++j) {
        f32 arcLen = 2.0f * PI * r / board.width() * 0.8f;
        for (i32 i = 0; i < board.width(); ++i) {
            if (board.elemAt(j, i)== BoardElem::T_EMPTY)
                continue;

            f32 arcLen = 2.0f * PI * r / board.width() * 0.8f;
            DrawTriangle(
                Vector2{r * cosf(i * angle), r * sinf(i * angle)},
                Vector2{r * cosf((i + 1) * angle), r * sinf((i + 1) * angle)},
                Vector2{(r + arcLen) * cosf((i + 1) * angle), (r + arcLen) * sinf((i + 1) * angle)},
                pickCellColor(board.elemAt(j, i))
            );
            DrawTriangle(
                Vector2{(r + arcLen) * cosf((i + 1) * angle), (r + arcLen) * sinf((i + 1) * angle)},
                Vector2{(r + arcLen) * cosf(i * angle), (r + arcLen) * sinf(i * angle)},
                Vector2{r * cosf(i * angle), r * sinf(i * angle)},
                pickCellColor(board.elemAt(j, i))
            );
        }
        r += arcLen;
    }
}

void Renderer::drawWiredBoard(Board& board) {
    f32 angle = 2.0f * PI / board.width();
    f32 r = 2.3f;
    for (i32 j = 0; j < board.height(); ++j) {
        f32 arcLen = 2.0f * PI * r / board.width() * 0.8f;
        for (i32 i = 0; i < board.width(); ++i) {
            f32 arcLen = 2.0f * PI * r / board.width() * 0.8f;
            DrawLineEx(
                Vector2{r * cosf(i * angle), r * sinf(i * angle)},
                Vector2{r * cosf((i + 1) * angle), r * sinf((i + 1) * angle)},
                0.05f, GRAY
            );
            DrawLineEx(
                Vector2{r * cosf((i + 1) * angle), r * sinf((i + 1) * angle)},
                Vector2{(r + arcLen) * cosf((i + 1) * angle), (r + arcLen) * sinf((i + 1) * angle)},
                0.05f, GRAY
            );
            DrawLineEx(
                Vector2{(r + arcLen) * cosf((i + 1) * angle), (r + arcLen) * sinf((i + 1) * angle)},
                Vector2{(r + arcLen) * cosf(i * angle), (r + arcLen) * sinf(i * angle)},
                0.05f, GRAY
            );
            DrawLineEx(
                Vector2{(r + arcLen) * cosf(i * angle), (r + arcLen) * sinf(i * angle)},
                Vector2{r * cosf(i * angle), r * sinf(i * angle)},
                0.05f, GRAY
            );
        }
        r += arcLen;
    }
}

Color Renderer::pickCellColor(BoardElem elem) {
    switch (elem) {
        case BoardElem::T_EMPTY: return RAYWHITE;
        case BoardElem::T_BLUE: return BLUE;
        case BoardElem::T_RED: return RED;
        case BoardElem::T_ORANGE: return ORANGE;
        case BoardElem::T_GREEN: return LIME;
    };
}
