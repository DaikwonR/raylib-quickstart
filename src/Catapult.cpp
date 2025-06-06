#include "Catapult.h"
#include "body.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"
#include "world.h"
#include "gui.h"

#include <iostream>;

void Catapult::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2.0f, m_height / 2.0f });
    m_world = new world();
    m_world->Initialize();

    CreateCatapult();
    Target();
    Bullet();
    gameOver = false;
}

void Catapult::Update()  
{  
   float dt = GetFrameTime();  

   if (gameOver)
   {
       if (IsKeyPressed(KEY_R))
       {
           Restart();
       }
       return;
   }

   if (IsKeyPressed(KEY_SPACE)) world::simulate = !world::simulate;  

   if (!world::simulate) return;  

   // Charging mechanism  
   if (IsKeyDown(KEY_C) && !charged && !isCharging)  
   {  
       isCharging = true;  
       chargeTime = 0.0f;  
   }  

   if (isCharging)  
   {  
       chargeTime += dt;  

       // Interpolate arm position while charging  
       float chargeProgress = std::min(chargeTime / maxChargeTime, 1.0f);  
       Vector2 currentArmPos = Vector2Lerp(startPos, armCharge, chargeProgress);  
       m_arm->position = currentArmPos;  

       // Update projectile position to follow arm
       if (m_projectile && !charged)  
       {  
           m_projectile->position = m_arm->position + Vector2{ 0.5f, 0.3f };  
           m_projectile->velocity = Vector2{ 0, 0 }; 
       }  

       if (chargeTime >= maxChargeTime)  
       {  
           charged = true;  
           isCharging = false;  
       }  

       // Release early if key is released  
       if (!IsKeyDown(KEY_C))  
       {  
           charged = true;  
           isCharging = false;  
       }  
   }  

   if (IsKeyDown(KEY_D) && (charged || isCharging))
   {
	   MoveCatapult(2.0f * dt);
   }
   else if (IsKeyDown(KEY_A) && (charged || isCharging))
   {
       MoveCatapult(-2.0f * dt);
   }

   // Fire catapult  
   if (IsKeyPressed(KEY_F) && charged)  
   {  
       Shoot(startPos, armCharge); 
       CheckGameOver();
   }  

   // Reset catapult  
   if (IsKeyPressed(KEY_R))  
   {  
       Reset();  
   }  

   // Check for target hit  
   if (m_projectile && m_target && !m_targetHit) 
   {  
       float distance = Vector2Distance(m_projectile->position, m_target->position);  
       if (distance - m_projectile->size <= (m_projectile->size + m_target->size))  
       {  
           m_targetHit = true;  
           m_score += 100;  
           m_target->ApplyForce(Vector2{ randomf(-5, 5), randomf(5, 10) }, Body::ForceMode::Impulse);  
           CheckGameOver();
       }  
   }  

   // Create new target if current one is hit and falls off screen  
   if (m_targetHit && m_target && m_target->position.y < -10)  
   {  
       Target();  
   }  

   // Auto-reset if projectile falls off screen  
   if (m_projectile && m_projectile->position.y < -10)  
   {  
       Reset();  
       CheckGameOver();
   }  

   Scene::Update();  
}

void Catapult::FixedUpdate()
{
    m_world->Step(Scene::fixedTimeStep);
}

void Catapult::Draw()
{
    m_camera->BeginMode();

    DrawGrid(10, 5, DARKGREEN);

    // Draw world (bodies and springs)
    m_world->Draw(*this);

    // Draw catapult arm line for better visualization
    if (m_base && m_arm)
    {
        DrawLine(m_base->position, m_arm->position, 5, DARKBROWN);
    }

    // Draw charge indicator
    if (isCharging)
    {
        const float ppu = m_camera->GetPPU();
        const Vector2 pos = { -6.0 * ppu, 3.0 * ppu };
		const Vector2 size = { 2.0f * ppu, 0.5f * ppu };
		const float chargeProgress = std::min(chargeTime / maxChargeTime, 1.0f);

		DrawRectangle(pos.x, pos.y, size.x * chargeProgress, size.y, ORANGE);
		DrawRectangleLinesEx(Rectangle{ pos.x, pos.y, size.x, size.y }, 2.0f * ppu, DARKGRAY);
    }

    m_camera->EndMode();
}

void Catapult::DrawGUI()
{
   // Draw instructions
   DrawTextEx(GetFontDefault(), "CATAPULT GAME", Vector2{ 10.0f, 10.0f }, 24, 1, WHITE);
   DrawTextEx(GetFontDefault(), "Hold C to charge catapult", Vector2{ 10.0f, 40.0f }, 16, 1, WHITE);
   DrawTextEx(GetFontDefault(), "Use A/D to move catapult left/right", Vector2{ 10.0f, 120.0f }, 16, 1, WHITE);
   DrawTextEx(GetFontDefault(), "Press F to fire", Vector2{ 10.0f, 60.0f }, 16, 1, WHITE);
   DrawTextEx(GetFontDefault(), "Press R to reset", Vector2{ 10.0f, 80.0f }, 16, 1, WHITE);
   DrawTextEx(GetFontDefault(), "Press SPACE to pause/unpause", Vector2{ 10.0f, 100.0f }, 16, 1, WHITE);

   // Draw score
   DrawTextEx(GetFontDefault(), TextFormat("Score: %d", m_score), Vector2{ 10.0f, 130.0f }, 20, 1, YELLOW);
   DrawTextEx(GetFontDefault(), TextFormat("Projectiles Fired: %d", m_projectilesFired), Vector2{ 10.0f, 155.0f }, 16, 1, WHITE);

   // Draw status
   if (isCharging)
   {
       DrawTextEx(GetFontDefault(), "CHARGING...", Vector2{ 10.0f, 180.0f }, 18, 1, ORANGE);
   }
   else if (charged)
   {
       DrawTextEx(GetFontDefault(), "READY TO FIRE!", Vector2{ 10.0f, 180.0f }, 18, 1, GREEN);
   }
   else
   {
       DrawTextEx(GetFontDefault(), "Hold C to charge", Vector2{ 10.0f, 180.0f }, 18, 1, GRAY);
   }

   if (m_targetHit)
   {
       DrawTextEx(GetFontDefault(), "TARGET HIT!", Vector2{ static_cast<float>(GetScreenWidth() / 2 - 60), static_cast<float>(GetScreenHeight() / 2) }, 24, 1, GREEN);
   }

   if (gameOver)
   {
       const char* message = (m_score / 100 >= 3) ? "You win!" : "You lose!";
       Color messageColor = (m_score / 100 >= 3) ? GREEN : RED;
       DrawTextEx(GetFontDefault(), message, Vector2{ static_cast<float>(GetScreenWidth() / 2 - 60), static_cast<float>(GetScreenHeight() / 2 - 30) }, 36, 1, messageColor);
       DrawTextEx(GetFontDefault(), "Press R to restart", Vector2{ static_cast<float>(GetScreenWidth() / 2 - 60), static_cast<float>(GetScreenHeight() / 2 + 10) }, 24, 1, WHITE);
   }
}

// Implementation of Catapult methods

void Catapult::CreateCatapult()
{
    // base
    m_base = m_world->CreateBody(Body::Type::Static, Vector2{ -3, -5 }, 100.0f, 0.3f, BROWN);

    // arm
    m_arm = m_world->CreateBody(Body::Type::Kinematic, startPos, 5.0f, 0.2f, DARKBROWN);
    m_arm->restitution = 0.1f;

    // spring
    float beginPos = Vector2Distance(m_base->position, startPos);
    m_spring = m_world->CreateSpring(m_base, m_arm, beginPos, springStiffness, springDamping);
}

void Catapult::MoveCatapult(float dt)
{
    m_arm->position.x += dt;
    armCharge.x += dt;
    startPos.x += dt;
    m_base->position.x += dt;

    // Update projectile position if it exists and hasn't been fired
    if (m_projectile && !charged)
    {
        m_projectile->position.x += dt;
    }

    // Update spring rest length
    if (m_spring) {
        m_spring->restLength = Vector2Distance(m_base->position, startPos);
    }
}

void Catapult::Shoot(Vector2 startPos, Vector2 charge)
{
    if (!charged || !m_projectile) return;
    
    Vector2 launchDirection = Vector2Normalize(m_arm->position - m_base->position);
    float force = 15.0f * (chargeTime / maxChargeTime);     
    Vector2 launchVelocity = launchDirection * force;

    m_projectile->ApplyForce(launchVelocity, Body::ForceMode::Velocity);
    
    m_arm->position = startPos;

    charged = false;
    m_projectilesFired++;
}

void Catapult::Reset()
{
    // Reset arm position
    m_arm->position = startPos;

    // Create new projectile
    Bullet();

    // Reset charge state
    charged = false;
    isCharging = false;
    chargeTime = 0.0f;
}

void Catapult::Bullet()
{

    // Create projectile at the arm position
    Vector2 projectilePos = m_arm->position + Vector2{ 0.5f, 0.3f };
    m_projectile = m_world->CreateBody(Body::Type::Dynamic, projectilePos, 1.0f, 0.15f, RED);
    m_projectile->restitution = 0.7f;
    m_projectile->gravityScale = 1.0f;
    m_projectile->damping = 0.1f;
}

void Catapult::Target()
{
    Vector2 targetPos = { -2.5f , 4.0f };
    m_target = m_world->CreateBody(Body::Type::Static, targetPos, 2.0f, 0.25f, YELLOW);
    m_target->restitution = 0.5f;
    m_target->gravityScale = 1.0f;
    m_targetHit = false;
}

void Catapult::CheckGameOver()
{
	int hits = m_score / 100;
	int misses = m_projectilesFired - hits;
	if (hits >= 3)
	{
		gameOver = true; 
	}
	else if (misses >= 3)
	{
		gameOver = true; 
	}
}

void Catapult::Restart()
{
	m_score = 0;
	m_projectilesFired = 0;
	gameOver = false;
	Reset();
	world::simulate = true;
    Reset();
    Target();
}
