#include "trigonometry_scene.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

float Vector2Length(const Vector2& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vector2 Vector2Normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	if (l == 0) return Vector2{ 0, 0 };
	return Vector2{v.x / l, v.y / l};
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);

	float radius = 3;
	float rate = 0.8f;
	float time = (float)GetTime() * rate;

	int steps = 50;

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;
		DrawCircle(Vector2{x, y}, 0.25f, RED);
	}

	for (float x = -9.0f; x < 9; x += 0.2f)
	{
		float theta = time + ((x / 18) * (2 + PI));
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;

		DrawCircle(Vector2{ x, c }, 0.25f, GREEN);
		DrawCircle(Vector2{ x, s }, 0.25f, BLUE);
	}

	float theta;

	/*DrawGrid(10, 5, WHITE);
	DrawCircleV(m_camera->WorldToScreen(Vector2{ 0, 0 }), m_camera->WorldToScreen(1), RED);*/

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
