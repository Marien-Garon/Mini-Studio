#include "SampleScene.h"

#include "Player.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<Player>(100, sf::Color::Red);
	pEntity1->SetPosition(300, 200);
	pEntity1->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		pEntity1->MoveLeft(pEntity1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		pEntity1->MoveRight(pEntity1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		pEntity1->TakeDamage(10);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		pEntity1->Heal(10);
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
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}