#include "Player.h"
#include "InputManager.h"

#include <iostream>

void Player::OnInitialize()
{
	SetSpeed(300);
}

void Player::OnUpdate()
{

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

void Player::Movement()
{
	InputManager& in = InputManager::Get();
	float deltaTime = GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Jump();

	SetDirection(0, 0);

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		SetDirection(1, 0);
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		SetDirection(-1, 0);
	}
}

void Player::Jump()
{
	StartGravity(-200);
}