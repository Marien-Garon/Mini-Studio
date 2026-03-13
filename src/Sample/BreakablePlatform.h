#pragma once
#include "Platform.h"

class BreakablePlatform : public Platform
{
private:
	float m_timer = 2.0f;

	bool isSteppedOn;

public:
	void OnCollision(Entity* player) override;
};

