#pragma once

#include <cassert>
#include "raylib.h"
#include "box2d/box2d.h"

enum EntityType {
    SPRITE,
    CIRCLE
};

struct Entity {
    bool alive = false;
    b2BodyId bodyId;
    EntityType type;
    Color color;
};


void createStaticBox(Entity *e, Color color);
