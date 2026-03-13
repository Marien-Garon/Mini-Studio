#pragma once
#include "PhysicalEntity.h"

class Player : public PhysicalEntity
{
public:

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override {};
	void OnInitialize() override {};
	void OnDestroy() override {};

	void TakeDamage(int damage);
	void Heal(int heal);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);

private:

	int m_health = 100;
	int m_maxHealth = 100;
	bool m_playerAlive = true;

	float m_maxSpeed = 50.f;
	float m_acceleration = 120.f;
	float m_deceleration = 100.f;

	// 1 droite, -1 gauche
	int m_direction = 1;
};