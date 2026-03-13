#pragma once
#include "Platform.h"




class BreakablePlatform : public Platform
{
private:
	float m_timer = 2.0f;

public:
	void OnCollision(Entity* player) override;
};

