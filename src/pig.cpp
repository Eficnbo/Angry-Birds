#include "pig.hpp"
#include <iostream>

Pig::Pig(float pos_X, float pos_Y, b2World* world) {

    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos_X, pos_Y);
    body = world->CreateBody(&bodyDef);
    hitpoints_ = new int(4);
    body->SetUserData(hitpoints_);
    body->SetBullet(true);

    b2CircleShape circle = b2CircleShape();
    circle.m_p.Set(0, 0);
    circle.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 100.0f;
    fixtureDef.restitution = 0;
    body->CreateFixture(&fixtureDef);

    graphicsitem_ = new PigGraphicsItem("green", pos_X, pos_Y);
}

Pig::~Pig(){
    delete hitpoints_;
    delete graphicsitem_;
}

int Pig::GetHitpoints(){
    return *hitpoints_;
}

b2Body* Pig::GetBody(){
    return body;
}

void Pig::UpdateGraphics(){
    graphicsitem_->SetPosition(body->GetPosition().x, body->GetPosition().y);
    float angle = body->GetAngle();
    graphicsitem_->SetRotation(angle);
}

PigGraphicsItem * Pig::GetGraphicsItem(){
    return graphicsitem_;
}
