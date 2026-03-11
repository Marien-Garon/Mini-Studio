#include "Player.h"

#include <iostream>

void Player::OnUpdate()
{
	float deltaTime = GetDeltaTime();
	sf::Vector2f position = GetPosition();
	position.x += m_speed;

	if (m_speed > 0.f)
	{
		m_speed -= m_deceleration * deltaTime;
		if (m_speed < 0.f) m_speed = 0.f;
	}
	else if (m_speed < 0.f)
	{
		m_speed += m_deceleration * deltaTime;
		if (m_speed > 0.f) m_speed = 0.f;
	}

	SetPosition(position.x, position.y);
}

void Player::OnCollision(Entity* other)
{
	std::cout << "Player::OnCollision" << std::endl;
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
	m_speed += m_acceleration * deltaTime;

	if (m_speed > m_maxSpeed)
	{
		m_speed = m_maxSpeed;
	}
	
}

void Player::MoveLeft(float deltaTime)
{
	m_speed -= m_acceleration * deltaTime;

	if (m_speed < -m_maxSpeed)
	{
		m_speed = -m_maxSpeed;
	}
}
