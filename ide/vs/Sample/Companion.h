#pragma once
#include "Entity.h"
#include "Player.h"

class Companion : public Entity
{
public:

	void OnUpdate() override;
	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void Follow(Player* _player);

};

