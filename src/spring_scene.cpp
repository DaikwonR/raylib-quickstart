#include "spring_scene.h"
#include "body.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"
#include "world.h"
#include "Gravitation.h"
#include "gui.h"

#include <iostream>

void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2.0f, m_height / 2.0f });
	m_world = new world();
	m_world->Initialize();
}

void SpringScene::Update()
{
	float dt = GetFrameTime();
	GUI::Update();

	float theta = randomf(0, 360);

	if (IsKeyPressed(KEY_SPACE)) world::simulate = !world::simulate;

	if (!GUI::mouseOverGUI)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::bodyTypeActive;

			Body* body = m_world->CreateBody(position, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			body->restitution = GUI::restitutionValue;
			body->gravityScale = GUI::gravityScaleValue;

		}	

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}

		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

				m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else
			{
				if (m_selectedBody && m_connectBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_connectBody->position);
					m_world->CreateSpring(m_selectedBody, m_connectBody, distance, 20);
				}
				m_selectedBody = nullptr;
				m_connectBody = nullptr;
			}
		}
	}

	// apply forces
	m_world->Step(dt);

	// apply collision
	for (auto body : m_world->GetBodies())
	{
		// keep the bodies inside the screen with restitution
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}

		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}
	}
}

void SpringScene::FixedUpdate()
{
	// apply forces
	m_world->Step(Scene::fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGREEN);

	//DrawCircle(Vector2{ 4, 2 }, 0.1f, BLUE);

	m_world->Draw(*this);

	if (m_selectedBody)
	{
		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		if (m_connectBody)
		{
			DrawCircleLine(m_connectBody->position, m_connectBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_connectBody->position, 3, GREEN);
		}
		else
		{
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}

	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}

