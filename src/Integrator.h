#pragma once

#include "body.h"
#include "raymath.h"

inline void ExplicitIntergrator(Body& body, float timeStep)
{
	body.position += (body.velocity * timeStep);
	body.velocity += (body.acceleration * timeStep);
	body.velocity *= 1.0f / (1.0f + (body.damping * timeStep));
}

inline void SemiImplicitIntergrator(Body& body, float timeStep)
{
	body.position += (body.velocity * timeStep);
	body.velocity += (body.acceleration * timeStep);

}