#pragma once

struct AABBCollider
{
	float x, y;
	float width, height;

	bool IsColliding(const AABBCollider& _other);

	bool IsInside(const AABBCollider& _other);

	bool IsInside(float _x, float _y);

	void SetPosition(float _x, float _y);
};
