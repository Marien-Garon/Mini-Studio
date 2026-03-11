#pragma once
#include "PhysicalEntity.h"

class Player : public PhysicalEntity
{
public:

	void OnCollision(Entity* other) override;
	void OnUpdate();

	void TakeDamage(int damage);
	void Heal(int heal);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);

private:

	int m_health = 100;
	int m_maxHealth = 100;
	bool m_playerAlive = true;

	float m_speed = 0.f;
	float m_maxSpeed = 50.f;
	float m_acceleration = 250.f;
	float m_deceleration = 200.f;

	sf::Vector2f m_position;
};