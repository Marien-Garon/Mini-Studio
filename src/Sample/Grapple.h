#pragma once
#include "Entity.h"

class Player;

class Grapple : public Entity
{
	Player* m_Owner;

	friend Player;
public:
	void OnInitialize() override;

	void OnUpdate() override;

	bool AsReachedTarget();

};