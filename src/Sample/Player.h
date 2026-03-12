#pragma once
#include "PhysicalEntity.h"

class Player : public PhysicalEntity
{
public:

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override {};
	void OnInitialize() override ;
	void OnDestroy() override {};

	void TakeDamage(int damage);
	void Heal(int heal);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Jump() override;
	void Attack();

private:

	int m_health = 100;
	int m_maxHealth = 100;
	bool m_playerAlive = true;

	float m_maxSpeed = 50.f;
	float m_acceleration = 250.f;
	float m_deceleration = 200.f;

	int m_numberOfGoodPress = 0;
	int m_numberOfBadPress = 0;
};