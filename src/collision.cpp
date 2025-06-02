#include "collision.h"
#include <raymath.h>
#include <math_utils.h>

void CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
   for (int i = 0; i < bodies.size(); i++) 
   {
       Body* bodyA = bodies[i];
       for (int j = i + 1; j < bodies.size(); j++)
       {
           Body* bodyB = bodies[j];
           // if both bodies are not dynamic
           if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic)
           {
               continue; 
           }
           if (Intersects(bodyA, bodyB))
           {
               Contact* contact = new Contact(); 
               contact->bodyA = bodyA;
               contact->bodyB = bodyB;

               // direction vector from bodyB to bodyA
               Vector2 direction = bodyA->position - bodyB->position;

               // get Vector2 Length squared of direction
               float distanceSqr = Vector2LengthSqr(direction);

               if (distanceSqr <= EPSILON)
               {
                   direction = Vector2{ randomf(-0.05, 0.05), randomf(-0.05f, 0.05f) };
                   distanceSqr = Vector2LengthSqr(direction);
               }

               float distance = sqrtf(distanceSqr);
               float radius = bodyA->size + bodyB->size;
               contact->depth = radius - distance;
               contact->normal = direction / distance;
               contact->restitution = 0.5f * (bodyA->restitution + bodyB->restitution);

               contacts.push_back(contact); 
           }
       }
   }
}

void SeperateContacts(contacts_t& contacts)
{
    for (auto contact : contacts)
    {
        float totalInverseMass = contact->bodyA->InvMass + contact->bodyB->InvMass;
        if (totalInverseMass <= 0.0f) continue; 

        Vector2 separation = contact->normal * (contact->depth / totalInverseMass);
        contact->bodyA->position = contact->bodyA->position + (separation * contact->bodyA->InvMass);
        contact->bodyB->position = contact->bodyB->position - (separation * contact->bodyB->InvMass);
    }
}

bool Intersects(Body* bodyA, Body* bodyB)
{
    // get distance between bodyA ad bodyB, use Vector2Distance;
    float distance = Vector2Distance(bodyA->position, bodyB->position);
    // add size of bodyA and bodyB
    float radius = bodyA->size + bodyB->size;

    return distance <= radius;
}