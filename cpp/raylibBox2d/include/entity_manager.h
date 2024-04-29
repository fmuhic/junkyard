#pragma once

#include "box2d/math_types.h"
#include "types.h"
#include "entity.h"
#include <vector>

struct EntityManager {
    EntityManager(i32 maxEntityCount);

    void createStaticBox(b2WorldId worldId, b2Vec2 p, Color color);
    void createDynamicBox(b2WorldId worldId, b2Vec2 p, Color color);
    Entity * getFirstFreeEntity();
    
    std::vector<Entity> entities;

    private:

    b2Polygon boxPolygon;
};
