#pragma once

#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_contact.h"

class ContactListener : public b2ContactListener{
public:
    ContactListener();

    void BeginContact(b2Contact* contact);

};
