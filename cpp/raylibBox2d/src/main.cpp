#include "raylib.h"

#include "config.h"
#include "game.h"

int main(void) {
    GameConfig config;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.screenWidth, config.screenHeight, config.windowName.c_str());
    SetTargetFPS(config.targetFps);

    Game *game = new Game(config);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        game->processInput();
        game->updateCamera();
        game->step(dt);
        game->draw();
    }

    CloseWindow();

    return 0;
}
