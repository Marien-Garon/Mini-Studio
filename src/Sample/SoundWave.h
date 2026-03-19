#pragma once
#include "Entity.h"

class AttackZone : public Entity
{
private:

	float m_lifeSpan = 1;
	int m_damage;
public:

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;


};