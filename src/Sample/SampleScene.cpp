#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"

#include "DummyEntity.h"

#include"Enemy.h"

#include"Utils.h"

#include"Platform.h"
#include"ClassicPlatform.h"
#include"BreakablePlatform.h"

#include "Debug.h"
#include "InputManager.h"
#include <iostream>

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100



#include <iostream>


void SampleScene::OnInitialize()
{
	//pEntity1 = CreateEntity<Enemy>(20,20, sf::Color::Red);
	//pEntity1->SetPosition(100, 100);
	//pEntity1->SetRigidBody(true);
	//pEntity1->SetMoveAble(true);
	//pEntity1->SetTag(1);

	//pEntity2 = CreateEntity<Enemy>(50,50, sf::Color::Green);
	//pEntity2->SetPosition(500, 500);
	//pEntity2->SetRigidBody(true);
	//pEntity2->SetMoveAble(true);

	//pEntitySelected = nullptr;
    
    Platform* pPlatform1 = CreateEntity<ClassicPlatform>(100, 20, sf::Color::Blue);
    pPlatform1->SetPosition(200, 300);
    m_Platforms.push_back(pPlatform1);

    Platform* pPlatform2 = CreateEntity<BreakablePlatform>(200, 20, sf::Color::Blue);
    pPlatform2->SetPosition(100, 300);
    m_Platforms.push_back(pPlatform2);

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

    for (auto p : m_Platforms)
    {
        p->OnUpdate(dt);
    }

    //pEntity1->Update(dt);

    //if (pEntitySelected != nullptr)
    //{
    //    sf::Vector2f position = pEntitySelected->GetPosition();
    //    Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    //}
}

void SampleScene::TrySetSelectedEntity(Enemy* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

