#pragma once

#include "blockgraphicsitem.h"
#include "box2d/b2_math.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world_callbacks.h"
#include <memory>
#include <iostream>

class Block{
public:
    Block(float pos_X, float pos_Y, std::string color, b2World* world);

    ~Block();

    int GetHitpoints();

    b2Body* GetBody();

    void UpdateGraphics();

    BlockGraphicsItem * GetGraphicsItem();

private:
    b2Body* body;
    BlockGraphicsItem* graphicsitem_;
    int* hitpoints_;
};
