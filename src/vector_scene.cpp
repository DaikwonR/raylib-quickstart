#include "vector_scene.h"
#include "world.h"
#include "scene.h"
#include "body.h"
#include "math_utils.h"

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	if (IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(), 1, 1));
			float theta = randomf(0, 360);
			float x = cos(theta);
			float y = sin(theta);
			body->velocity = Vector2{ x, y } * randomf(1, 6);
		};
		}

	}

	m_world->Step(dt);

}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
