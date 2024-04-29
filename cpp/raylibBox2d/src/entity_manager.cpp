#include "entity_manager.h"
#include <cassert>

EntityManager::EntityManager(i32 maxEntityCount) {
    entities.reserve(maxEntityCount);
    for (i32 i = 0; i < maxEntityCount; ++i)
        entities.push_back(Entity{});

    //Hardcoded for now
    boxPolygon = b2MakeSquare(0.5f * 1.0f);
}

Entity * EntityManager::getFirstFreeEntity() {
    for (auto &e: entities) {
        if (!e.alive)
            return &e;
    }
    assert(false && "We should always have space to create new entity");
}

void EntityManager::createStaticBox(b2WorldId worldId, b2Vec2 p, Color color) {
    Entity *e = getFirstFreeEntity();

    e->alive = true;
    e->type = EntityType::SPRITE;
    e->color = color;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = p; ;

    e->bodyId = b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(e->bodyId, &shapeDef, &boxPolygon);
}

void EntityManager::createDynamicBox(b2WorldId worldId, b2Vec2 p, Color color) {
    Entity *e = getFirstFreeEntity();

    e->alive = true;
    e->type = EntityType::SPRITE;
    e->color = color;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = p; ;

    e->bodyId = b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.restitution = 0.1f;

    b2CreatePolygonShape(e->bodyId, &shapeDef, &boxPolygon);
}
