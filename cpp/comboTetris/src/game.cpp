#include "game.h"
#include "board.h"
#include "raylib.h"

Game::Game(GameConfig gameConfig):
    board(gameConfig.boardWidth, gameConfig.boardHeight)
{
    config = gameConfig;

    Camera2D camera = {};
    camera.target = Vector2 { 0.0f, 0.0f };
    camera.offset = Vector2 { config.screenWidth / 2.0f, config.screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = config.baseCameraZoom;

    renderer = Renderer();

    createScene();
}

void Game::processInput() {
    if (IsKeyPressed(KEY_F))
        ToggleFullscreen();
}

void Game::updateCamera() {
    i32 width = GetScreenWidth();
    i32 height = GetScreenHeight();
    f32 newZoom = config.baseCameraZoom;

    if (width * config.sceneHeightInTiles >= height * config.sceneWidthInTiles)
        newZoom *= height / config.sceneHeightInTiles ;
    else
        newZoom *= width / config.sceneWidthInTiles;

    camera.offset = { width / 2.0f, height / 2.0f };
    camera.zoom = newZoom;
}

void Game::step([[maybe_unused]]f32 dt) {
    // board.debuBoard();
}

void Game::draw() {
    renderer.draw(camera, board);
}

void Game::createScene() {
    board.createTestBoard();
}
