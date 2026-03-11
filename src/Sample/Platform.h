#pragma once

#include "Entity.h"

class Platform : public Entity
{
public:
	virtual void OnInitialize() {};
	virtual void OnUpdate() {};

	virtual void Breakable(float dt) {};
	virtual void Under() {};
};

