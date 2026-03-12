#include "Player.h"
#include "InputManager.h"

#include <iostream>

void Player::OnInitialize()
{
	SetSpeed(300);
}

void Player::OnUpdate()
{
	InputManager& in = InputManager::Get();
	float deltaTime = GetDeltaTime();

	
	Movement();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		TakeDamage(1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Heal(1);
	}

	//if (mSpeed > 0.f)
	//{
	//	mSpeed -= m_deceleration * deltaTime;
	//	if (mSpeed < 0.f)
	//		mSpeed = 0.f;
	//}
	//else if (mSpeed < 0.f)
	//{
	//	mSpeed += m_deceleration * deltaTime;
	//	if (mSpeed > 0.f)
	//		mSpeed = 0.f;
	//}



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

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		GoToPosition(GetPosition().x + mSpeed * deltaTime, GetPosition().y);
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		GoToPosition(GetPosition().x - mSpeed * deltaTime, GetPosition().y);
	}
}
