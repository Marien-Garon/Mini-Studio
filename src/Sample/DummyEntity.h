#pragma once
#include "Entity.h"

class DummyEntity : public Entity
{
public:

	void OnUpdate() override;
	void OnCollision(Entity* other) override;

	void SetColor();
	/*void OnCollision(Entity* other) override;*/
};

