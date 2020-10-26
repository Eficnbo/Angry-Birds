#include "bird.hpp"
#include <iostream>

Bird::Bird(float x, float y, std::string color, bool ability_available, b2World* world)
    : ability_available_(ability_available) {
        thrown_ = false;
        in_slingshot_ = false;

        b2BodyDef bodyDef = b2BodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        body = world->CreateBody(&bodyDef);
        body->SetUserData(nullptr);
        body->SetBullet(true);
        body->SetAngularDamping(5);

        b2CircleShape circle = b2CircleShape();
        circle.m_p.Set(0, 0);
        circle.m_radius = 0.3f;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 100.0f;
        body->CreateFixture(&fixtureDef);

        graphicsitem_ = new BirdGraphicsItem(color, x, y);

    }

Bird::~Bird(){
    delete graphicsitem_;
}

bool Bird::IsThrown(){
    return thrown_;
}

void Bird::SetPosition(float x, float y) {
    body->SetTransform(b2Vec2(x,y),body->GetAngle());
    graphicsitem_->SetPosition(x, y);
}

void Bird::UpdateGraphics(){
    if(in_slingshot_ == false) {
        graphicsitem_->SetPosition(body->GetPosition().x, body->GetPosition().y);
        float angle = body->GetAngle();
        graphicsitem_->SetRotation(angle);
    }
}

void Bird::Throw(float speed, float angle){
    float x = cos(angle)*speed;
    float y = sin(angle)*speed;
    body->ApplyLinearImpulseToCenter( 5*b2Vec2(x,y), true );
    thrown_ = true;
    in_slingshot_ = false;
}

bool Bird::AbilityAvailable(){
    return ability_available_;
}

void Bird::ActivateAbility(){
    if(ability_available_ == true){
        body->ApplyLinearImpulse(body->GetLinearVelocity(), body->GetWorldCenter(), true);
        ability_available_ = false;
    }
}

b2Body* Bird::GetBody(){
    return body;
}

void Bird::SetToSlingshot() {
    in_slingshot_ = true;
}

BirdGraphicsItem * Bird::GetGraphicsItem(){
    return graphicsitem_;
}

