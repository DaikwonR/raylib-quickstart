#include "Gravitation.h"  
#include "raymath.h"  

void ApplyGravitation(bodies_t& bodies, float strength)  
{  
   for (int i = 0; i < bodies.size(); i++)  
   {  
       Body* bodyA = bodies[i];  

       for (int j = i + 1; j < bodies.size(); j++)  
       {  
           Body* bodyB = bodies[j];  

           // STEP 1: Find the direction vector from bodyB to bodyA  
           Vector2 direction = { bodyA->position.x - bodyB->position.x, bodyA->position.y - bodyB->position.y };  

           // STEP 2: Get the distance between the two bodies  
           float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);  

           // STEP 3: Clamp the distance to a minimum value to avoid extreme force  
           distance = std::max(distance, 1.0f);  

           // STEP 4: Calculate gravitational force magnitude using:  
           // forceMagnitude = (bodyA mass * bodyB mass / (distance * distance)) * strength;  
           float forceMagnitude = (bodyA->mass * bodyB->mass / (distance * distance)) * strength;  

           // STEP 5: Normalize the direction vector and scale it by the force magnitude  
           Vector2 directionNormalized = { direction.x / distance, direction.y / distance };  
           Vector2 forceVector = { directionNormalized.x * forceMagnitude, directionNormalized.y * forceMagnitude };  

           // STEP 6: Apply the force to both bodies (equal and opposite)  
           Vector2 negativeForceVector = { -forceVector.x, -forceVector.y };  
           bodyA->ApplyForce(negativeForceVector);  
           bodyB->ApplyForce(forceVector);  
       }  
   }  
}
