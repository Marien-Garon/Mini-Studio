#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"

#include "DummyEntity.h"

#include"Enemy.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
    pEntity1 = CreateEntity<Enemy>(50, sf::Color::Red);
    pEntity1->SetPosition(600, 600);
    pEntity1->SetRigidBody(true);

    pEntity1->Initialize(); 
}

void SampleScene::OnUpdate()
{
    float dt = GetDeltaTime(); 

    pEntity1->Update(dt);

    if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }
}


void SampleScene::TrySetSelectedEntity(Enemy* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	pEntity1->OnUpdate();
	pEntity2->OnUpdate();


	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
	}
}