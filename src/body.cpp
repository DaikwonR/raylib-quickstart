#include "body.h"
#include "Integrator.h"
#include "raymath.h"
#include "world.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	// apply gravity
	force += (world::gravity * gravityScale) * mass;
	// compute acceleration
	acceleration = (force * InvMass);

	SemiImplicitIntergrator(*this, dt);

	velocity *= 1.0f / (1.0f + (damping * dt));
}

void Body::Draw(const Scene& scene)
{

	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;
}
