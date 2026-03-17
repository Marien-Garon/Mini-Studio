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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		StopFall();

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		GoToPosition(GetPosition().x + mSpeed/* * deltaTime*/, GetPosition().y);
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))
	{
		GoToPosition(GetPosition().x - mSpeed/* * deltaTime*/, GetPosition().y);
	}
}

void Player::Jump()
{
	StartGravity(-150);
	m_isJumping = true;
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

void Player::MoveRight()
{
	float deltaTime = GetDeltaTime();

	mSpeed += mAcceleration * deltaTime;
	SetDirection(1, 0, mBaseSpeed + (mAcceleration * deltaTime));

}

void Player::MoveLeft()
{
	float deltaTime = GetDeltaTime();

	mSpeed += mAcceleration * deltaTime;
	SetDirection(-1, 0, mBaseSpeed + (mAcceleration * deltaTime));

}

Hook* Player::SearchForHook()
{
	std::vector<Hook*> hooks = GetScene<SampleScene>()->GetHooks();

	Hook* closestHook = nullptr;
	float closestDistance = m_grappleRopeLenght;
	for (int i = 0; i < hooks.size(); i++) {
		if (hooks[i]->GetPosition().y > GetPosition(0.5f, 1.f).y) {
			continue;
		}

		if (m_directionFacing == true)
		{
			if (hooks[i]->GetPosition().x < GetPosition(0.5f, 1.f).x) {
				continue;
			}
		}

		else
			if (hooks[i]->GetPosition().x > GetPosition(0.5f, 1.f).x) {
				continue;
			}
		

		float currentDistance = Utils::GetDistance(GetPosition().x, GetPosition().y, hooks[i]->GetPosition().x, hooks[i]->GetPosition().y);
		if (currentDistance <= m_grappleRopeLenght) {
			if (currentDistance < closestDistance) {
				closestDistance = currentDistance;
				closestHook = hooks[i];
			}
		}
	}
	return closestHook;
}

void Player::ThrowGrapple(Hook* target)
{
	if (target == nullptr || m_grapple != nullptr) {
		return;

	mGravitySpeed = 300;
	mTarget.position.y = GetPosition().y - jumpSize;
	GoToDirection(GetPosition().x, mTarget.position.y);

	isJumping = true;
}