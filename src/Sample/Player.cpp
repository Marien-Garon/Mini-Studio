#include "Player.h"

#include <iostream>

void Player::OnUpdate()
{
	m_deltaTime = GetDeltaTime();
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

void Player::MoveRight(Player* player)
{
	m_speed += m_acceleration * 100;

	if (m_speed > m_maxSpeed)
	{
		m_speed = m_maxSpeed;
		m_position = player->GetPosition();
		player->GoToPosition(m_position.x -= 10.f, m_position.y, 100);
	}
	
}

void Player::MoveLeft(Player* player)
{
	m_speed += m_acceleration;

	if (m_speed > m_maxSpeed)
	{
		m_speed = m_maxSpeed;
		m_position = player->GetPosition();
		player->GoToPosition(m_position.x += 10.f, m_position.y, 100);
	}
}
