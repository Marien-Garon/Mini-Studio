#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"

#include "DummyEntity.h"

#include"Enemy.h"

#include"Utils.h"

#include"Platform.h"
#include"BreakablePlatform.h"

#include "Debug.h"
#include "InputManager.h"

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100


void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<Enemy>(20,20, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);
	pEntity1->SetMoveAble(true);
	pEntity1->SetTag(1);

	pEntity2 = CreateEntity<Enemy>(50,50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);
	pEntity2->SetMoveAble(true);

	m_Platforms.push_back(CreateEntity<Platform>(200, 50, sf::Color::Blue));
	m_Platforms[0]->SetPosition(500, 550);

	pEntitySelected = nullptr;

}

void SampleScene::OnEvent(const sf::Event& event)
{
    sf::Vector2f position = pEntity1->GetPosition();

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right)
    {
        float dist = Utils::GetDistance(position.x, position.y, 100.f, 100.f);

        if (dist > 10)
        {
            pEntity1->GoToPosition(position.x, position.y, 100.f);
        }
    }
}


void SampleScene::OnUpdate()
{

}

void SampleScene::TrySetSelectedEntity(Enemy* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

