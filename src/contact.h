#pragma once
#include <spring_scene.h>

struct Contact
{
	struct Body* bodyA;
	struct Body* bodyB;

	float restitution;

	float depth;

	Vector2 normal;
};