#pragma once

#include <cassert>
#include "raylib.h"

enum EntityType {
    SPRITE,
    CIRCLE
};

struct Entity {
    bool alive = false;
    EntityType type;
    Color color;
};


void createStaticBox(Entity *e, Color color);
