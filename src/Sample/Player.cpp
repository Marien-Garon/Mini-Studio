#include "Player.h"

#include <iostream>

void Player::OnUpdate()
{
	PhysicalEntity::OnUpdate();

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

	SetPosition(position.x, position.y);
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

void Player::Attack(int _damage)
{
	sf::Vector2f position = GetPosition();
	float deltaTime = GetDeltaTime();

	m_attack = CreateEntity<PhysicalEntity>(50, 50, sf::Color::Red);

	m_attack->SetPosition(position.x + 150 , position.y - 300);
	m_attack->Fall(deltaTime);
}
