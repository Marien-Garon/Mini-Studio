#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	void OnCollision(Entity* other) override;
	void TakeDamage(int damage);
	void Heal(int heal);

private:

	int m_health = 100;
	int m_maxHealth = 100;
};