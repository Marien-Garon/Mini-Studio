#include "Companion.h"
#include "SampleScene.h"
#include "Player.h"

#include <iostream>

void Companion::OnInitialize()
{
	sf::Vector2 playerPosition = static_cast<SampleScene*>(GetScene())->GetPlayer()->GetPosition();

	SetPosition(playerPosition.x - 100, playerPosition.y - 50);
	SetSpeed(50);
	GoToPosition(GetPosition().x, GetPosition().y - m_ondulation);
	m_basePosition = GetPosition();
}

void Companion::OnUpdate()
{
	sf::Vector2 playerPosition = static_cast<SampleScene*>(GetScene())->GetPlayer()->GetPosition();

	//if (GetPosition().y == m_basePosition.y - m_ondulation)
	//	GoToPosition(GetPosition().x, m_basePosition.y + m_ondulation);
	//
	//if (GetPosition().y == m_basePosition.y + m_ondulation)
	//	GoToPosition(GetPosition().x, m_basePosition.y - m_ondulation);

	if (GetPosition().x < playerPosition.x - 100)
		SetPosition(playerPosition.x - 100, GetPosition().y);

	if (GetPosition().x > playerPosition.x - 100)
		SetPosition(playerPosition.x - 100, GetPosition().y);

	GetShape()->setFillColor(sf::Color::Blue);

	if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		GetShape()->setFillColor(sf::Color::Red);
	
	
}

void Companion::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}