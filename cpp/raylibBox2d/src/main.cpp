#include "raylib.h"
#include "box2d/box2d.h"

#include "types.h"
#include <iostream>

#define BASE_GAME_WIDTH 32
#define BASE_GAME_HEIGHT 18
#define BASE_WINDOW_WIDTH 1280
#define BASE_WINDOW_HEIGHT 720
#define BASE_ZOOM 1.0f

void drawSprite(Vector2 p, f32 width, f32 height, f32 rotation, Color color) {
    DrawRectanglePro(
        Rectangle { p.x - width * 0.5f, -p.y - height * 0.5f, width, height },
        Vector2 { 0.0f, 0.0f },
        rotation,
        color
    );
}

void updateScreenResolution(Camera2D& camera) {
    i32 newWidth = GetScreenWidth();
    i32 newHeight = GetScreenHeight();
    f32 newZoom = BASE_ZOOM;
    [[maybe_unused]] f32 aspectRatio = newWidth / newHeight;

    if (newWidth * BASE_GAME_HEIGHT >= newHeight * BASE_GAME_WIDTH)
        newZoom *= newHeight / (f32) BASE_GAME_HEIGHT;
    else
        newZoom *= newWidth / (f32) BASE_GAME_WIDTH;

    camera.offset = { newWidth / 2.0f, newHeight / 2.0f };
    camera.zoom = newZoom;
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);

    Camera2D camera = {};
    camera.target = Vector2 { 0.0f, 0.0f };
    camera.offset = Vector2 { 1280 / 2.0f, 720 / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            
        }

        updateScreenResolution(camera);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

            for (i32 i = -16; i < 16; i++) {
                for (i32 j = -9; j < 9; j++) {
                    drawSprite(Vector2 { (f32) i, (f32) j }, 0.95f, 0.95f, 0.0f, BLUE);
                }
            }

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
