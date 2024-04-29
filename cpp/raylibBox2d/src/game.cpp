#include "game.h"
#include "entity_manager.h"

Game::Game(GameConfig gameConfig):
    entityManager(gameConfig.maxEntityCount)
{
    config = gameConfig;

    b2WorldDef worldDef = b2DefaultWorldDef();
	worldId = b2CreateWorld(&worldDef);

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

void Game::step(f32 dt) {
    b2World_Step(worldId, dt, config.box2dIterationCount);
}

void Game::draw() {
    renderer.draw(entityManager.entities, camera);
}

// Move this into seperate LevelCreator class
void Game::createScene() {
    i32 groundEntityCount = 20;
	for (int i = 0; i < groundEntityCount; ++i)	{
        entityManager.createStaticBox(
            worldId,
            b2Vec2 { (1.0f * i - 10.0f) * config.tileSize, -4.5f - 0.5f * config.tileSize },
            GREEN
        );
	}

    i32 dynamicBoxCount = 6;
	for (int i = 0; i < dynamicBoxCount; ++i)	{
        entityManager.createDynamicBox(
            worldId,
            b2Vec2 { 0.5f * config.tileSize * i, -4.0f + config.tileSize * i },
            BLUE
        );
	}
}
