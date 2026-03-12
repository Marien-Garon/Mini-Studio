#include <iostream>
#include "InputManager.h"
#include "SampleScene.h"
#include "PhysicalEntity.h"
#include "Companion.h"
#include "Player.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"

void SampleScene::OnInitialize()
{
	m_player = CreateEntity<Player>(100, 200, sf::Color::Red);
	m_robot = CreateEntity<Companion>(50, 50, sf::Color::Blue);

	
	
	
	
	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
}

void SampleScene::TrySetSelectedEntity(Player* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	InputManager& in = InputManager::Get();
	float deltaTime = GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_player->Jump();
	}
	if (in.GetJoystickLeftX(0) >= 100.f)
	{
		std::cout << in.GetJoystickLeftX(0);
		m_player->MoveRight(deltaTime);
	}

	if (in.GetJoystickLeftX(0) <= -100.f)
	{
		std::cout << in.GetJoystickLeftY(0);
		m_player->MoveLeft(deltaTime);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_player->MoveLeft(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player->MoveRight(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		m_player->TakeDamage(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player->Heal(10);
	}

	
	/*if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
	}*/

	IncreaseTimer();
}

bool SampleScene::IsAttackTimingOkay()
{
	if (test_timerAttaque >= test_tempsEntreLesAttaque - 5.f / 60.f || test_timerAttaque <= 5.f / 60.F)
		return true;

	return false;
}

void SampleScene::IncreaseTimer()
{
	test_timerAttaque += GetDeltaTime();

	if (test_timerAttaque >= test_tempsEntreLesAttaque)
	{
		test_timerAttaque = 0;
		std::cout << "\n" << std::endl;
	}

}
