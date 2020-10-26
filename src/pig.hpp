#pragma once

#include "pig_graphics_item.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world_callbacks.h"
#include <memory>

class Pig{
public:
    Pig(float pos_X, float pos_Y,b2World* world);
    ~Pig();
    int GetHitpoints();
    b2Body* GetBody();
    void UpdateGraphics();
    PigGraphicsItem * GetGraphicsItem();

private:
    b2Body* body;
    PigGraphicsItem* graphicsitem_;
    int* hitpoints_;
};
