#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	void OnCollision(Entity* other) override;
	void TakeDamage(int damage);
	void Heal(int heal);
	void MoveRight(Player* player);
	void MoveLeft(Player* player);

private:

	int m_health = 100;
	int m_maxHealth = 100;
	bool m_playerAlive = true;
};