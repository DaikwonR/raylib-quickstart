#include "vector_scene.h"
#include "body.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"
#include "world.h"
#include "Gravitation.h"
#include "gui.h"

#include <iostream>

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2.0f, m_height / 2.0f });
	m_world = new world();
	m_world->Initialize();
}

void VectorScene::Update()
{
	float dt = GetFrameTime();
	GUI::Update();

	float theta = randomf(0, 360);

	if (!GUI::mouseOverGUI && IsMouseButtonDown(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		Body::Type type = (Body::Type)GUI::bodyTypeActive;


		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			float offset = randomf(-180, 180);
			float x = cosf((theta + offset) * DEG2RAD);
			float y = sinf((theta + offset) * DEG2RAD);

			body->velocity = Vector2{ x, y } * randomf(1, 6);
			body->restitution = GUI::restitutionValue;
			body->gravityScale = GUI::gravityScaleValue;
		};
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

void VectorScene::FixedUpdate()
{
	// apply forces
	m_world->Step(Scene::fixedTimeStep);
}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGREEN);
	
	//DrawCircle(Vector2{ 4, 2 }, 0.1f, BLUE);

	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	GUI::Draw();	
}

