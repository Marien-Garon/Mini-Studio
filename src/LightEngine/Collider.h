#pragma once

enum class Side
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	INSIDE,
	NONE
};


struct AABBCollider
{
public:

	float x, y;
	float width, height;

	bool IsColliding(const AABBCollider& _other);

	bool IsInside(const AABBCollider& _other);

	bool IsInside(float _x, float _y);

	void SetPosition(float _x, float _y);

	Side GetCollisionSide(const AABBCollider& _other);
};
