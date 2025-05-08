#include "world.h"
#include "body.h"

world::~world()
{
}

void world::Initialize(Vector2 gravity, int poolSize)
{
	m_gravity = gravity;
	m_bodies.reserve(poolSize);
}

Body* world::CreateBody(const Vector2& position, float size, const Color& color)
{
	Body* body = new Body( position, size, color );
	m_bodies.push_back(body);

    return body;
}

void world::Step(float timeStep)
{
	for (auto body : m_bodies) 
	{
		body->Step(timeStep);
	}
}

void world::Draw(const Scene& scene)
{
	for (auto body : m_bodies)
	{
		body->Draw(scene);
	}	
}

void world::DestoryAll()
{
	for (auto body : m_bodies)
	{
		delete body;
	}
	m_bodies.clear();
}
