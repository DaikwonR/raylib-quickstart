#pragma once

#include "scene.h"
#include "body.h"
#include "spring.h"

class Catapult : public Scene
{
	public:
		Catapult(const char* name, int width, int height, Color bgColor)
			: Scene(name, width, height, bgColor)
		{}
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Draw() override;
		void DrawGUI() override;

public:
	void CreateCatapult();
	void MoveCatapult(float dt);
	void Shoot(Vector2 pos, Vector2 charge);
	void Reset();
	void Bullet();
	void Target();
    void CheckGameOver();
    void Restart();

    // Catapult components
    Body* m_base = nullptr;           
    Body* m_arm = nullptr;            
    Spring* m_spring = nullptr;  

	float minX = -8.0f;
	float maxX = 2.0f;

    // Game objects
    Body* m_projectile = nullptr;     
    Body* m_target = nullptr;         

    // Catapult parameters
    Vector2 startPos = { -3, -2 };
    Vector2 armCharge = { -3, -4 };
    float springStiffness = 50.0f;
    float springDamping = 5.0f;

    // Game state
    bool charged = false;
    bool isCharging = false;
    float chargeTime = 0.0f;
    float maxChargeTime = 2.0f;

    // Score tracking
    int m_score = 0;
    int m_projectilesFired = 0;
    bool m_targetHit = false;
    bool gameOver = false;

};