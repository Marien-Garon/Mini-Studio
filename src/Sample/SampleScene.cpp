#include <iostream>
#include "InputManager.h"
#include "SampleScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"

void SampleScene::OnInitialize()
{
	player = CreateEntity<Player>(100, 200, sf::Color::Red);

	player->SetPosition(300, 200);
	player->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->Jump();
	}
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

	if (in.GetJoystickLeftX(0) >= 100.f)
	{
		std::cout << in.GetJoystickLeftX(0);
		player->MoveRight(deltaTime);
	}

	if (in.GetJoystickLeftX(0) <= -100.f)
	{
		std::cout << in.GetJoystickLeftY(0);
		player->MoveLeft(deltaTime);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		player->MoveLeft(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->MoveRight(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		player->TakeDamage(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->Heal(10);
	}

	/*if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
	}*/
}