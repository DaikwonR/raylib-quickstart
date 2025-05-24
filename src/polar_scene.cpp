#include "polar.h"
#include "polar_scene.h"

#define LOGARITHMICSHAPE

//PolarScene::PolarScene(const std::string& title, int width, int height, const Color& background)
//{
//
//}



void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2 });
}

void PolarScene::Update()
{
}

void PolarScene::FixedUpdate()
{

}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

#ifdef ARCHIMEDEAN
	int steps = 200;
	float time = (float)GetTime();
	float a = 0;
	float b = 0.35f;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (8.0f * PI);
		float r = a + (b * theta);
		Polar p(time + theta, r);
		DrawCircle(p, 0.01f, BLUE);
	}
#elif defined CARDIOID
	int steps = 360;
        float time = (float)GetTime() * 0.1f;
        float a = 2.0f;

		for (int i = 0; i < steps; i++)
		{
			float theta = (i / (float)steps) * (2.0f * PI);
			float r = a * (1 + cosf(theta));
			Polar p(time + theta, r);
			DrawCircle(p, 0.01f, BLUE);
		}

#elif defined LIMACON
	int steps = 360;
	float time = (float)GetTime() * 0.1f;
	float a = 2.0f;
	float b = 1.0f;

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2.0f * PI);
		float r = a + (b * cosf(theta));
		Polar p(time + theta, r);
		DrawCircle(p, 0.01f, BLUE);
	}
#elif defined ROSE
	int steps = 360;
	float time = (float)GetTime() * 0.1f;
	float a = 2.0f;
	float k = 2.0f;

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (4.0f * PI);
		float r = a * cosf(k * theta);
		Polar p(time + theta, r);
		DrawCircle(p, 0.01f, RED);
	}
#elif defined LOGARITHMICSHAPE
	int steps = 360;
	float time = (float)GetTime() * 0.1f;
	float a = 2.0f;
	float b = 1.0f;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2.0f * PI);
		float r = a * expf(b * theta);
		Polar p(time + theta, r);
		DrawCircle(p, 0.01f, RED);
	}

#endif // ARCHIMEDEAN
	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
