#pragma once

#include "board.h"
#include "raylib.h"
#include "config.h"
#include "renderer.h"
#include "types.h"

struct Game {
    Game(GameConfig config);

    void processInput();
    void updateCamera();
    void step(f32 dt);
    void draw();

    private:

    void createScene();

    Board board;
    GameConfig config;
    Camera2D camera;
    Renderer renderer;
};
