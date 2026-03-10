#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<PhysicalEntity>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetSpeed(100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateEntity<PhysicalEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetSpeed(100);
	pEntity2->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		pEntity1->Jump();
		pEntity2->Jump();
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		pEntity1->StopFall();
		pEntity2->StopFall();
	}

	if (event.mouseButton.button == sf::Mouse::Button::Middle)
	{
		pEntity1->Fall(GetDeltaTime());
		pEntity2->Fall(GetDeltaTime());
	}
	
}

void SampleScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	pEntity1->OnUpdate();
	pEntity2->OnUpdate();

	count++;
	std::cout << count << std::endl;


	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}