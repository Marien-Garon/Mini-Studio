#pragma once

#include "Platform.h"


class ClassicPlatform : public Platform
{
public:
	ClassicPlatform(float width, float height, const sf::Color& color) {};

	void CheckCollision(AABBCollider& playerCollider, PhysicalEntity* player) override;

	void OnUpdate(float dt) override;
	void OnPlayerContact()override;
};