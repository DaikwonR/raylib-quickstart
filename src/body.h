#pragma once

#include "raylib.h"
#include "aabb.h"

struct Body
{
public:

	enum class Type
	{
		Static,
		Dynamic,
		Kinematic
	};

	enum class ForceMode
	{
		Force,
		Impulse,
		Velocity
	};

public:

	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		size{ size },
		color{ color }
	{}

	Body(const Vector2& position, float size, const Color& color) :
		position{ position },
		size{ size },
		color{ color }
	{}
	Body(Type type, const Vector2& position, float mass, float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		InvMass = (type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}

	void Step(float dt);
	void Draw(const class Scene& scene);

	void ApplyForce(const Vector2& force, ForceMode forceMode = ForceMode::Force);
	void ClearForce() { force = Vector2{ 0, 0 }; }

	aabb GetAABB() const { return aabb{ position, { size * 2, size * 2 } }; }

public:

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };

	float mass{ 1 };
	float InvMass{ 1 };

	float gravityScale{ 1 };
	float restitution{ 1 };

	// restitution
	float m_restitution{ 0.5f };

	float size = 1;
	float damping = 0.1f;
	Color color = WHITE;

	Type type = Type::Dynamic;

	Body* next{ nullptr };
	Body* prev{ nullptr };
};