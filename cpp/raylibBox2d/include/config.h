#pragma once

#include <string>
#include "types.h"

#define MAX_ENTITY_COUNT 100
#define TARGET_FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE_METERS 1.0f
#define BASE_CAMERA_ZOOM 1.0f
#define SCENE_WIDTH_IN_TILES 32
#define SCENE_HEIGHT_IN_TILES 18
#define BOX2D_PHYSICS_ITERATION_COUNT 8

struct GameConfig {
    std::string windowName = "Game"; 
    i32 maxEntityCount = MAX_ENTITY_COUNT;
    i32 targetFps = TARGET_FPS;
    i32 screenWidth = SCREEN_WIDTH;
    i32 screenHeight = SCREEN_HEIGHT;
    f32 tileSize = TILE_SIZE_METERS;
    f32 baseCameraZoom = BASE_CAMERA_ZOOM;
    f32 sceneWidthInTiles = SCENE_WIDTH_IN_TILES;
    f32 sceneHeightInTiles = SCENE_HEIGHT_IN_TILES;
    i32 box2dIterationCount = BOX2D_PHYSICS_ITERATION_COUNT;
};
