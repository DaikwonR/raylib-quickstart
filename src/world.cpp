#include "world.h"
#include "body.h"
#include "gravitation.h"
#include "gui.h"
#include "collision.h"

world::~world()
{

}

void world::Initialize(Vector2 gravity, int poolSize)
{
	world::gravity = gravity;
	m_bodies.reserve(poolSize);
}

Body* world::CreateBody(const Vector2& position, float size, const Color& color)
{
	Body* body = new Body(position, size, color);
	m_bodies.push_back(body);

	return body;
}

Body* world::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
	Body* body = new Body(type, position, mass, size, color);
	m_bodies.push_back(body);

	return body;
}

void world::Step(float timeStep)
{
	if (!simulate) return;

	if (gravitation > 0)
	{
		ApplyGravitation(m_bodies, gravitation);
	}

	for (auto body : m_bodies)
	{
		body->Step(timeStep);
		body->ClearForce();
	}
	for (auto spring : m_springs)
	{
		spring->ApplyForce(springStiffnessMultiplier);
	}

	m_contacts.clear();
	CreateContacts(m_bodies, m_contacts);
	SeperateContacts(m_contacts);
}

void world::Draw(const Scene& scene) 
{
	for (auto body : m_bodies)
	{
		body->Draw(scene);
	}
	for (auto spring : m_springs)
	{
		spring->Draw(scene);
	}
}

Spring* world::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping)
{
	Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
	m_springs.push_back(spring);

	return spring;
}

void world::DestoryAll()
{
	for (auto body : m_bodies)
	{
		delete body;
	}
	for (auto spring : m_springs)
	{
		delete spring;
	}
	m_bodies.clear();
	m_springs.clear();
}
