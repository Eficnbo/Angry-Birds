#pragma once

#include "bird_graphics_item.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world_callbacks.h"
#include <math.h>
#include <fstream>
#include <memory>

class Bird{
public:
    Bird(float x, float y, std::string color, bool ability_available, b2World* world);

    ~Bird();

    bool IsThrown();

    void SetPosition(float x, float y);

    void UpdateGraphics();

    void Throw(float speed, float angle);

    bool AbilityAvailable();

    void ActivateAbility();

    b2Body* GetBody();

    void SetToSlingshot();

    BirdGraphicsItem * GetGraphicsItem();

private:
    bool thrown_;
    bool ability_available_;
    bool in_slingshot_;
    b2Body* body;
    BirdGraphicsItem *graphicsitem_;
};
