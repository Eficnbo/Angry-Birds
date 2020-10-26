#include "block.hpp"


Block::Block(float pos_X, float pos_Y, std::string color, b2World* world) {
    if(color == "lightBrown" || color == "blue" || color == "gray"){
        b2BodyDef bodyDef = b2BodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos_X, pos_Y);
        body = world->CreateBody(&bodyDef);
        if(color == "lightBrown"){
            hitpoints_ = new int(10);
        }
        else if(color == "blue"){
            hitpoints_ = new int(6);
        }
        else if(color == "gray"){
            hitpoints_ = new int(17);
        }
        body->SetUserData(hitpoints_);
    }
    else if(color == "darkBrown"){
        b2BodyDef BodyDef = b2BodyDef();
        BodyDef.position.Set(pos_X, pos_Y);
        body = world->CreateBody(&BodyDef);
        hitpoints_ = new int(10000);
        body->SetUserData(hitpoints_);
    }
    b2Vec2 vertices[4];

    vertices[0].Set( (-0.5f), (0.5f));
    vertices[1].Set( (-0.5f), (-0.5f));
    vertices[2].Set( (0.5f), (-0.5f));
    vertices[3].Set( (0.5f),  (0.5f));

    b2PolygonShape polygonShape = b2PolygonShape();
    polygonShape.Set(vertices, 4);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    if(color == "lightBrown" || color == "darkBrown"){
        fixtureDef.density = 10;
    }
    else if(color == "blue"){
        fixtureDef.density = 5;
    }
    else if(color == "gray"){
        fixtureDef.density = 30;
    }
    fixtureDef.friction = 1;
    body->CreateFixture(&fixtureDef);

    graphicsitem_ = new BlockGraphicsItem(color, pos_X, pos_Y);

}

Block::~Block(){
    delete hitpoints_;
    delete graphicsitem_;
}

int Block::GetHitpoints(){
    return *hitpoints_;
}

b2Body* Block::GetBody(){
    return body;
}

void Block::UpdateGraphics(){
    graphicsitem_->SetPosition(body->GetPosition().x, body->GetPosition().y);
    float angle = body->GetAngle();
    graphicsitem_->SetRotation(angle);
}

BlockGraphicsItem * Block::GetGraphicsItem(){
    return graphicsitem_;
}
