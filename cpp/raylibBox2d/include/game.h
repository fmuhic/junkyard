#pragma once

#include "box2d/box2d.h"
#include "entity_manager.h"
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

    EntityManager entityManager;
    GameConfig config;
    b2WorldId worldId;
    Camera2D camera;
    Renderer renderer;
};
