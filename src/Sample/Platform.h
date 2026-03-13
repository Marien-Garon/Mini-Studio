#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
};
	
