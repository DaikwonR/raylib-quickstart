#pragma once

#include "raylib.h"
#include "scene_camera.h"
#include "scene.h"
#include <string>

class PolarScene : public Scene
{
public:
	PolarScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{

	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

	bool IsQuit() { return WindowShouldClose(); }

	void SetCamera(SceneCamera* camera) { m_camera = camera; }
	SceneCamera* GetCamera() { return m_camera; }

	friend struct Body;
};
