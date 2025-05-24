#pragma once
#include "scene.h"
#include "raylib.h"


struct Spring
{
public:
	struct Body* bodyA;
	struct Body* bodyB;
	float restLength;
	float k; // stiffness

public:
	Spring() = default;
	Spring(Body* bodyA, Body* bodyB, float restLength, float k) :
		bodyA{ bodyA },
		bodyB{ bodyB },
		restLength{ restLength },
		k{ k }
	{
	}

	void ApplyForce(float damping = 0.5f, float kMultiplier = 1);
	void ApplyForce(const Vector2& position, Body& body, float restLength, float k, float damping);
	void Draw(const Scene& scene);
};