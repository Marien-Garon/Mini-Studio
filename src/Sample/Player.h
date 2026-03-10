#pragma once
#include "PhysicalEntity.h"

struct PlayerParameter
{
	float m_minSpeed = 50.f;
	float m_maxSpeed = 100.f;
	float m_acceleration = 25.f;
	float m_deceleration = 75.f;
};

class Player : public PhysicalEntity
{
public:

	void OnCollision(Entity* other) override;
	void OnUpdate();

	void TakeDamage(int damage);
	void Heal(int heal);
	void MoveRight(Player* player);
	void MoveLeft(Player* player);

private:

	int m_health = 100;
	int m_maxHealth = 100;
	bool m_playerAlive = true;
	float m_deltaTime;

	float m_speed = 70.f;
	float m_maxSpeed = 100.f;
	float m_acceleration = 25.f;
	float m_deceleration = 75.f;

	sf::Vector2f m_position;
};