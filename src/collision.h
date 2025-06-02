#pragma once
#include <world.h>

void CreateContacts(const bodies_t& bodies, const contacts_t& contacts);
void SeperateContacts(contacts_t& contacts);

bool Intersects(Body* bodyA, Body* bodyB);