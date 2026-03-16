#include "Player.h"
#include "InputManager.h"
#include "SoundWave.h"
#include "SoundBlast.h"
#include "SampleScene.h"
#include "Grapple.h"
#include "Hook.h"
#include "Utils.h"

#include <iostream>

void Player::OnInitialize()
{
	mBaseSpeed = 300;
	mAcceleration = 0.f;
	mDecceleration = 0.f;
	mMaxSpeed = 0.f;

	SetSpeed(300);
	m_grappleRopeLenght = 200.f;
}


void Player::OnUpdate()
{
	if (m_grapple != nullptr) {
		if (GetPosition().x == m_grapple->GetPosition().x && GetPosition().y == m_grapple->GetPosition().y) {
			m_grapple->Destroy();
			m_grapple = nullptr;
			GoToPosition(GetPosition().x + 10.f, GetPosition().y);
		}
	}
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

void Player::Actions()
{
	InputManager& in = InputManager::Get();
	float deltaTime = GetDeltaTime();

	if (in.IsControllerPressed(0, Controller::Button::RB) || in.IsKeyPressed(sf::Keyboard::LShift)) {
		ThrowGrapple(SearchForHook());
	}

	if (in.IsControllerPressed(0, Controller::Button::A) || in.IsKeyHeld(sf::Keyboard::Space))
		Jump();

	SetDirection(0, 0);

	if (in.GetJoystickLeftX(0) >= 100.f || in.IsKeyHeld(sf::Keyboard::D))
	{
		m_directionFacing = true;
		MoveRight();
	}

	if (in.GetJoystickLeftX(0) <= -100.f || in.IsKeyHeld(sf::Keyboard::Q))	
	{
		m_directionFacing = false;
		MoveLeft();
	}

	if (in.IsControllerPressed(0, Controller::Button::LB) || in.IsKeyPressed(sf::Keyboard::Enter))
	{
		Attack();
	}

	else if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		m_numberOfGoodPress = 0;

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

		if (hooks[i]->GetPosition().x < GetPosition(0.5f, 1.f).x) {
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
	}
	m_grapple = CreateEntity<Grapple>(20.f, 20.f, sf::Color::Magenta);
	m_grapple->SetPosition(GetPosition().x + 1, GetPosition().y + 1);
	m_grapple->m_Owner = this;

	m_grapple->GoToPosition(target->GetPosition().x, target->GetPosition().y);
}
