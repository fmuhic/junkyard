#include "renderer.h"
#include "raylib.h"
#include <iostream>

Renderer::Renderer() {
}

void Renderer::draw(std::vector<Entity>& entities, Camera2D &camera) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

        for (auto &e: entities) {
            if (!e.alive)
                continue;
            
            drawEntity(e);
        }

    EndMode2D();
    EndDrawing();
}

void Renderer::drawEntity(Entity& e) {
    f32 angle = -RAD2DEG * b2Body_GetAngle(e.bodyId);
    f32 width = 1.0f;
    f32 height = 1.0f;

    switch (e.type) {
        case EntityType::SPRITE: {
            b2Vec2 p = b2Body_GetWorldPoint(e.bodyId, b2Vec2 { -0.5f * 1.0f, 0.5f * 1.0f });
            DrawRectanglePro(
                Rectangle { p.x - width * 0.5f, -p.y - height * 0.5f, width, height },
                Vector2 { 0.0f, 0.0f },
                angle,
                e.color
            );
        } break;
        case EntityType::CIRCLE: {
            b2Vec2 p = b2Body_GetWorldPoint(e.bodyId, b2Vec2 { 0.0f, 0.0f });
            DrawCircleSector(
                Vector2 { p.x - width * 0.5f, -p.y - height * 0.5f },
                0.5f,
                angle,
                angle + 355.0f,
                32,
                e.color
            );
        } break;
    }
}
