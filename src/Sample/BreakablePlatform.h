#pragma once

#include "Platform.h"
#include"PhysicalEntity.h"

class BreakablePlatform : public Platform
{
private:
	float m_timer;
	bool IsSteppedOn;
	bool IsBroken = false;
public:

	BreakablePlatform(float width, float height, const sf::Color& color) {};

	void OnUpdate(float dt) override;
	void CheckCollision(AABBCollider& playerCollider, PhysicalEntity* player) override;
	void OnPlayerContact() override;
};