#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"
#include "Debug.h"
#include "InputManager.h"

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100



#include "AssetManager.h"

void SampleScene::OnInitialize()
{
    AssetManager& AM = AssetManager::getInstance();

	pEntity1 = CreateEntity<Enemy>(AM.LoadSprite("sheet", 0, 0, 460, 600), sf::Color::Red);
    pEntity1->SetSpriteScale(0.5f, 0.5f);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);
	pEntity1->SetMoveAble(true);
	pEntity1->SetTag(1);

	pEntity2 = CreateEntity<Enemy>(50,50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);
	pEntity2->SetMoveAble(true);

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
    float dt = GetDeltaTime();

    pEntity1->Update(dt);

    InputManager& im = InputManager::Get();

    if (im.IsControllerHeld(0,Controller::Button::A))
        std::cout << "Test" << std::endl;


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

//void SampleScene::OnUpdate()
//{
//
//	if(pEntitySelected != nullptr)
//	{
//		sf::Vector2f position = pEntitySelected->GetPosition();
//		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
//	}
//}