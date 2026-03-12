#pragma once
#include "Entity.h"

class Companion : public Entity
{
public:
	void OnCollision(Entity* other) override;
};

