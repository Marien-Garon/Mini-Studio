#include <iostream>

#include "SampleScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"

void SampleScene::OnInitialize()
{
	player = CreateEntity<Player>(100, sf::Color::Red);
	player->SetPosition(300, 200);
	player->SetRigidBody(true);

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
	float deltaTime = GetDeltaTime();

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->Jump();
	}

	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
	}
}