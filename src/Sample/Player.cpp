#include "Player.h"
#include "InputManager.h"

#include <iostream>

void Player::OnInitialize()
{
	SetSpeed(300);
	m_Translation = { 0,0 };
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

	if (isJumping == true)
	{
		if (GetPosition().y <= mTarget.position.y)
		{
			isJumping = false;
			isFalling = true;
			Fall(GetDeltaTime());
		}
	}

	GoToPosition(GetPosition().x + m_Translation.x, GetPosition().y + m_Translation.y);



	m_Translation = { 0, (m_Translation.y + mSpeed * deltaTime) * isJumping};

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		StopFall();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		m_Translation.x += mSpeed * deltaTime;
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		m_Translation.x -= mSpeed * deltaTime;
	}
}

void Player::Jump()
{
	if (isFalling == true || isJumping == true)
		return;

	m_Translation.y -= jumpSize;
	GoToPosition(GetPosition().x, GetPosition().y - jumpSize);

	isJumping = true;
}