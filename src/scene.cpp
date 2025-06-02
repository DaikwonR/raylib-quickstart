#include "scene.h"
#include "scene_camera.h"
#include "world.h"
#include <rlgl.h>

Scene::Scene(const std::string& title, int width, int height, const Color& background) :
	m_width{ width },
	m_height{ height },
	m_background{ background }
{
	InitWindow(width, height, title.c_str());
}

Scene::~Scene()
{
	CloseWindow();
}

void Scene::Update()
{
	aabb worldAABB = m_camera->GetAABB();


	for (auto body : m_world->GetBodies())
	{
		aabb aabb = body->GetAABB();		

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

        if ((aabb.min().x) < worldAABB.min().x)
        {
			float overlap = (worldAABB.min().x - aabb.min().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
        }
        else if (aabb.max().x > worldAABB.max().x)
        {
			float overlap = (worldAABB.max().x - aabb.max().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
        }
	}
}

void Scene::BeginDraw()
{
	BeginDrawing();
	ClearBackground(m_background);
	DrawFPS(20, 20);
}

void Scene::EndDraw()
{
	EndDrawing();
}

void Scene::DrawGrid(float slices, float thickness, const Color& color) const
{
	for (float i = -slices; i <= slices; i++)
	{
		DrawLineEx(m_camera->WorldToScreen(Vector2{ -slices, i }), m_camera->WorldToScreen(Vector2{ slices, i }), thickness, color);
		DrawLineEx(m_camera->WorldToScreen(Vector2{ i, -slices }), m_camera->WorldToScreen(Vector2{ i, slices }), thickness, color);
	}
}

void Scene::DrawText(const std::string& text, const Vector2& world, int fontSize, Color& color) const
{
	Vector2 screen = m_camera->WorldToScreen(world);

	rlPushMatrix();
	rlTranslatef(screen.x, screen.y, 0);
	rlScalef(1, -1, 1);  // flip back so text is upright
	::DrawText(text.c_str(), 0, 0, fontSize, color);
	rlPopMatrix();
}

void Scene::DrawCircle(const Vector2& world, float radius, Color& color) const
{
	DrawCircleV(m_camera->WorldToScreen(world), m_camera->WorldToScreen(radius), color);
}

void Scene::DrawCircleLine(const Vector2& world, float radius, Color& color, int pixels) const
{
	DrawCircleLinesV(m_camera->WorldToScreen(world), m_camera->WorldToScreen(radius) + pixels, color);
}

void Scene::DrawLine(const Vector2& v1, const Vector2& v2, float thickness, Color& color) const
{
	DrawLineEx(m_camera->WorldToScreen(v1), m_camera->WorldToScreen(v2), thickness, color);
}
