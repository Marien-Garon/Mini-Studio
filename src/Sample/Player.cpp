#include "Player.h"
#include "SampleScene.h"
#include "InputManager.h"

#include <iostream>

void Player::OnUpdate()
{
	float deltaTime = GetDeltaTime();
	sf::Vector2f position = GetPosition();
	position.x += mSpeed;

	if (mSpeed > 0.f)
	{
		mSpeed -= m_deceleration * deltaTime;
		if (mSpeed < 0.f) 
			mSpeed = 0.f;
	}
	else if (mSpeed < 0.f)
	{
		mSpeed += m_deceleration * deltaTime;
		if (mSpeed > 0.f) 
			mSpeed = 0.f;
	}

	SetPosition(position.x, GetPosition().y);

	
}

void Player::OnInitialize()
{
	SetRigidBody(true);
	SetPosition(300, 200);
}

void Player::TakeDamage(int _damage)
{
	if (m_health <= 0)
	{
		m_health = 0;
		std::cout << "Player died." << std::endl;
		m_playerAlive = false;
	}

	else {

		m_health -= _damage;
		std::cout << "Player take damage : " << _damage << std::endl;
		std::cout << "Current Health : " << m_health << std::endl;
	}
}

void Player::Heal(int _heal)
{
	if (m_health >= 100)
	{
		m_health = m_maxHealth;
		std::cout << "Player had max health" << std::endl;
	}

	else {

		m_health += _heal;
		std::cout << "Player got heal : " << _heal << std::endl;
		std::cout << "Current Health : " << m_health << std::endl;
	}
}

void Player::MoveRight(float deltaTime)
{
	mSpeed += m_acceleration * deltaTime;

	if (mSpeed > m_maxSpeed)
	{
		mSpeed = m_maxSpeed;
	}
	
}

void Player::MoveLeft(float deltaTime)
{
	mSpeed -= m_acceleration * deltaTime;

	if (mSpeed < -m_maxSpeed)
	{
		mSpeed = -m_maxSpeed;
	}
}

void Player::Jump()
{
	std::cout << "Player Jump called\n";
	PhysicalEntity::Jump();
}

void Player::Attack()
{
	InputManager IM = InputManager::Get();
	bool isAttackingTimingGood = static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay();

	if (IM.)
}
