#pragma once

struct AABBCollider
{
	float x, y;
	float width, height;

	bool IsColliding(const AABBCollider& _other);

	bool IsInsideAABB(const AABBCollider& _other);
};

//Deprecated and never used yay
bool IsCollidingAABB(const AABBCollider& _c1, const AABBCollider& _c2);

bool IsInsideAABBB(const AABBCollider& _c1, const AABBCollider& _c2);