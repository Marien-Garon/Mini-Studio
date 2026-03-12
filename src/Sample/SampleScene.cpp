#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"

#include"Enemy.h"
#include "Camera.h"

#include"Utils.h"

#include "Debug.h"
#include "InputManager.h"
#include <iostream>

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100



#include <iostream>


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

    mCamera = CreateEntity<Camera>(0, 0, sf::Color::Green);

    mCamera->SetupCamera(2, pEntity1);
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
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        mCamera->Shake(10);
    }
    if (event.mouseButton.button == sf::Mouse::Middle)
    {
        pEntity1->Fall(GetDeltaTime());
    }


}


//void SampleScene::OnUpdate()
//{
//    float dt = GetDeltaTime();
//
//    pEntity1->Update(dt);
//
//    if (pEntitySelected != nullptr)
//    {
//        sf::Vector2f position = pEntitySelected->GetPosition();
//        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
//    }
//}

void SampleScene::TrySetSelectedEntity(Enemy* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
    GetGameManager()->RefreshCamera(mCamera);

	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue); 
	}
}