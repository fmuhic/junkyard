#include "box2d/math_types.h"
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

struct Entity {
    b2BodyId bodyId;
};

void DrawEntity(const Entity* entity) {
    b2Vec2 p = b2Body_GetWorldPoint(entity->bodyId, b2Vec2 { -0.5f * 1.0f, 0.5f * 1.0f });
    float radians = b2Body_GetAngle(entity->bodyId);
    drawSprite(Vector2 {p.x, p.y}, 1.0f, 1.0f, -RAD2DEG * radians, RED);
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


    f32 tileSize = 1.0f;
    b2WorldDef worldDef = b2DefaultWorldDef();
	b2WorldId worldId = b2CreateWorld(&worldDef);

    b2Polygon tilePolygon = b2MakeSquare(0.5f * 1.0f);

    Entity groundEntities[20] = {};
	for (int i = 0; i < 20; ++i)
	{
		Entity* entity = groundEntities + i;
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.position = b2Vec2 {(1.0f * i - 10.0f) * tileSize, -4.5f - 0.5f * tileSize };

		entity->bodyId = b2CreateBody(worldId, &bodyDef);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		b2CreatePolygonShape(entity->bodyId, &shapeDef, &tilePolygon);
	}

    Entity boxEntities[6] = {};
	for (int i = 0; i < 6; ++i)
	{
		Entity* entity = boxEntities + i;
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2{ 0.5f * tileSize * i, -4.0f + tileSize * i };
		entity->bodyId = b2CreateBody(worldId, &bodyDef);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.restitution = 0.1f;
		b2CreatePolygonShape(entity->bodyId, &shapeDef, &tilePolygon);
	}


    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F))
            ToggleFullscreen();

        float deltaTime = GetFrameTime();
        b2World_Step(worldId, deltaTime, 6);

        updateScreenResolution(camera);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

            for (int i = 0; i < 20; ++i)
                DrawEntity(groundEntities + i);

            for (int i = 0; i < 6; ++i)
                DrawEntity(boxEntities + i);

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
