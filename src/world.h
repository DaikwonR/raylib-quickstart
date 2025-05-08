#pragma once

#include <vector>
#include "raylib.h"

struct Body;
class Scene;

class world
{
public:

	~world();

	void Initialize(Vector2 gravity = Vector2{ 0 ,-9.81 }, int poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timeStep);
	void Draw(const Scene& scene);

	void DestoryAll();

private:
	Vector2 m_gravity{ 0, -9.81 };
	std::vector<Body*> m_bodies;

};