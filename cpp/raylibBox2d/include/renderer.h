#pragma once

#pragma once

#include <vector>
#include "raylib.h"
#include "box2d/box2d.h"
#include "entity.h"
#include "types.h"

struct Renderer {
    Renderer();

    void draw(std::vector<Entity>& entities, Camera2D &camera);

    private:

    void drawEntity(Entity& e);
};

