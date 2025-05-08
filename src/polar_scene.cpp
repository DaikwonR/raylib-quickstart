#include "polar.h"
#include "polar_scene.h"

void PolarScene::DrawGrid(float slices, float thickness, const Color& color) const
{
	const float maxRadius = 300.0f;
	const Vector2 center = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	for (float r = 50.0f; r <= maxRadius; r += 50.0f)
	{
		DrawCircle(center, r, color);
	}

	for (int i = 0; i < slices; i++)
	{
		float angle = (i * 2.0f * PI) / slices;
		Polar p(angle, maxRadius);
		Vector2 end = p;
		end.x += center.x;
		end.y += center.y;
		DrawLine(center, end, thickness, color);
	}
}

void PolarScene::DrawText(const std::string& text, const Vector2& world, int fontSize, Color& color) const
{
}

void PolarScene::DrawCircle(const Vector2& world, float radius, Color& color) const
{
}

void PolarScene::DrawLine(const Vector2& v1, const Vector2& v2, float thickness, Color& color) const
{
}

PolarScene::PolarScene(const std::string& title, int width, int height, const Color& background)
{
}

PolarScene::~PolarScene()
{
}

void PolarScene::BeginDraw()
{
}

void PolarScene::EndDraw()
{
	DrawGrid(12, 2.0f, GRAY);
	
}
