#pragma once
#include "Entity.h"
class Player : public Entity
{
public:

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override {};
	void OnDestroy() override {} ;

	void TakeDamage(int damage);
	void Heal(int heal);

	void Movement();

	void Jump();

private:

	int m_health = 3;
	int m_maxHealth = 3;
	bool m_playerAlive = true;
	sf::Vector2f m_Translation;
	bool m_directionFacing = true; //true = regarde vers la droite, false = regarde vers la gauche

	float m_maxSpeed = 50.f;
	float m_acceleration = 250.f;
	float m_deceleration = 200.f;
};
