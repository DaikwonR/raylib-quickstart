#pragma once
#include "raylib.h"
#include "raymath.h"

struct Polar
{
public:
	Polar() = default;
	Polar(float angle, float radius) :
		angle{ angle },
		radius{ radius }
	{
	}

	Polar(Vector2 v) :
		// !!get angle from Vector2 !!
		angle{ atan2f(v.y, v.x) },
		// !!get vector length !!
		radius{ Vector2Length(v) }
	{
	}

	Polar& operator = (const Vector2& v)
	{
		// !!get angle from Vector2 !!
		angle = atan2f(v.y, v.x);
		// !!get vector length !!
		radius = { Vector2Length(v) };

		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		// !!get x position using cos(angle)* radius !!
		v.x = cosf(angle) * radius;
		// !!get y position using sin(angle)* radius !!
		v.y = sinf(angle) * radius;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};