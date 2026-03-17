#pragma once
#include "Platform.h"

class UnderPlatform : public Platform
{
public :
	void OnCollision(Entity* entity) override;
};
