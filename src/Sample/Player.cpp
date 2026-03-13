#include "Player.h"
#include "InputManager.h"
#include "SoundWave.h"
#include "SoundBlast.h"
#include "SampleScene.h"

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

	if (in.IsControllerPressed(0, Controller::Button::A) || in.IsKeyHeld(sf::Keyboard::Space))
		Jump();

	SetDirection(0, 0);

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		m_directionFacing = true;
		SetDirection(1, 0);
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))	
	{
		m_directionFacing = false;
		SetDirection(-1, 0);
	}

	if (in.IsControllerPressed(0, Controller::Button::LB) || in.IsKeyPressed(sf::Keyboard::Enter))
	{
		Attack();
	}
	else if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		m_numberOfGoodPress = 0;

	std::cout << m_numberOfGoodPress << std::endl;
}

void Player::Jump()
{
	StartGravity(-200);
}

void Player::Attack()
{
	float windowWidth = GetScene()->GetWindowWidth();
	bool isAttackingTimingGood = static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay();

	if (isAttackingTimingGood)
	{
		m_numberOfGoodPress++;
	}
		

	else
	{
		m_numberOfGoodPress = 0;
	}
		


	if (m_numberOfGoodPress == 1)
	{
		SoundWave* attack = CreateEntity<SoundWave>(50, 50, sf::Color::Cyan);
		attack->SetPosition(GetPosition().x, GetPosition().y);
		attack->GoToDirection(windowWidth * m_directionFacing, GetPosition().y);
		
	}

	else if (m_numberOfGoodPress == 3)
	{
		SoundBlast* attack = CreateEntity<SoundBlast>(50, 100, sf::Color::Cyan);
		attack->SetPosition(GetPosition().x, GetPosition().y);
		attack->GoToDirection(windowWidth * m_directionFacing, GetPosition().y);
		m_numberOfGoodPress = 0;
	}

	
}
