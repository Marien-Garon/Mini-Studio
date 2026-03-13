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
	void Attack();

	void MoveRight();
	void MoveLeft();


private:

	int m_health = 3;
	int m_maxHealth = 3;
	bool m_playerAlive = true;
	bool m_directionFacing = true; //true = regarde vers la droite, false = regarde vers la gauche
	int m_numberOfGoodPress = 0;

	float mAcceleration = 0.f;
	float mDecceleration = 0.f;
	float mBaseSpeed = 0.f;
	float mMaxSpeed = 0.f;


};
