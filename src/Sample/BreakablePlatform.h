#pragma once

#include "Platform.h"

class BreakablePlatform : public Platform
{
private:
	float m_timer;
	float m_maxTimer = 2.0f;
	bool IsSteppedOn = false;
public:

	BreakablePlatform(float width, float height, const sf::Color& color) {};

	void OnUpdate(float dt) override;
	void OnPlayerContact() override;
};