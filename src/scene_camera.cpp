#include "trigonometry_scene.h"
#include "rlgl.h"

void SceneCamera::BeginMode()
{
	m_camera.zoom = m_camera.offset.y / (m_size * m_ppu);

	rlDisableBackfaceCulling();
	rlPushMatrix();

	rlTranslatef(m_camera.offset.x, m_camera.offset.y, 0.0f);
	rlScalef(m_camera.zoom, -m_camera.zoom, 1.0f);
	rlRotatef(m_camera.rotation, 0.0f, 0.0f, 1.0f);
	rlTranslatef(-m_camera.target.x, -m_camera.target.y, 0.0f);
}

void SceneCamera::EndMode()
{
	rlPopMatrix();
}

Vector2 SceneCamera::ScreenToWorld(const Vector2& screen)
{
	float screenX = screen.x - m_camera.offset.x;
	float screenY = screen.y - m_camera.offset.y;

	float worldX =  screenX / (m_camera.zoom * m_ppu) + m_camera.target.x;
	float worldY = -screenY / (m_camera.zoom * m_ppu) + m_camera.target.y;

	return Vector2{ worldX, worldY };
}

Vector2 SceneCamera::WorldToScreen(const Vector2& world)
{
	return Vector2{ world.x * m_ppu, world.y * m_ppu };
}

//void TrigonometryScene::Initialize()
//{
//	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
//}
//
//float Vector2Length(const Vector2& v)
//{
//	return sqrtf((v.x * v.x) + (v.y * v.y));
//}
//
//Vector2 Vector2Normalize(const Vector2& v)
//{
//	float l = Vector2Length(v);
//	if (l == 0) return Vector2{ 0, 0 };
//	return Vector2{ v.x / l, v.y / l };
//}
//
//void TrigonometryScene::Draw()
//{
//	m_camera->BeginMode();
//
//	DrawGrid(10, 5, WHITE);
//
//	float radius = 3;
//	float rate = 0.8f;
//	float time = (float)GetTime() * rate;
//
//	int steps = 50;
//
//	for (int i = 0; i < steps; i++)
//	{
//		float theta = (i / (float)steps) * (2 * PI);
//		float x = cosf(theta) * radius;
//		float y = sinf(theta) * radius;
//		DrawCircle(Vector2{ x, y }, 0.25f, RED);
//	}
//
//	for (float x = -9.0f; x < 9; x += 0.2f)
//	{
//		float theta = time + ((x / 18) * (2 + PI));
//		float c = cosf(theta) * radius;
//		float s = sinf(theta) * radius;
//
//		DrawCircle(Vector2{ x, c }, 0.25f, GREEN);
//		DrawCircle(Vector2{ x, s }, 0.25f, BLUE);
//	}
//
//	float theta;
//
//	/*DrawGrid(10, 5, WHITE);
//	DrawCircleV(m_camera->WorldToScreen(Vector2{ 0, 0 }), m_camera->WorldToScreen(1), RED);*/
//
//	m_camera->EndMode();
//}
//
//void TrigonometryScene::DrawGUI()
//{
//}


