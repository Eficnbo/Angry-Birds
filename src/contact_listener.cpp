#include "contact_listener.hpp"

ContactListener::ContactListener() { }

void ContactListener::BeginContact(b2Contact *contact) {
    if(contact->GetFixtureA()->GetBody()->GetUserData() != nullptr){
        int* a = static_cast<int*>(contact->GetFixtureA()->GetBody()->GetUserData());
        *a -= 1;
    }
    if(contact->GetFixtureB()->GetBody()->GetUserData() != nullptr){
        int* b = static_cast<int*>(contact->GetFixtureB()->GetBody()->GetUserData());
        *b -= 1;
    }
}
