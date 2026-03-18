#pragma once

#include <SFML/System/Vector2.hpp>

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
	float bWidth, bHeight;

	AABBCollider(float _x, float _y, float _w, float _h);
	AABBCollider() {}; // Default constructor because without that the code go hugghhhh and die

	bool IsColliding(const AABBCollider& _other);

	bool IsInside(const AABBCollider& _other);

	bool IsInside(float _x, float _y);

	void SetPosition(float _x, float _y);

	void SetScale(float _x, float _y);

	void SetScale(const sf::Vector2f& _scale);

	void Move(sf::Vector2f _direction);
	void Move(float _x, float _y);

	Side GetCollisionSide(const AABBCollider& _other);
};
