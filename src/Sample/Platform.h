#pragma once

#include "Entity.h"

class Platform : public Entity
{
public:

	virtual void Draw() {};

	virtual void Breakable(float dt) {};
};

