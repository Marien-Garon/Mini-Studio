#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"

#include "AssetManager.h"
#include "Camera.h"
#include "Hook.h"


#include"Platform.h"
#include"BreakablePlatform.h"

#include"Entity.h"

#include "Debug.h"
#include "InputManager.h"

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100


void SampleScene::OnInitialize()
{
    AssetManager& AM = AssetManager::getInstance();

   m_player= CreateEntity<Player>(50, 50, sf::Color::Red);
   m_player->SetPosition(500, 500);

   m_robot = CreateEntity<Companion>(50, 50, sf::Color::Blue);
   m_robot->SetPosition(m_player->GetPosition().x - 150.f, m_player->GetPosition().y - 150.f);
   m_robot->SetOwner(m_player);

   mCamera = CreateEntity<Camera>(0, 0, sf::Color::Black);
   mCamera->SetupCamera(3, m_player);
   /*CAMERA SPEED HERE*/

   for (int i = 0; i < 3; i++) {
	   m_hooks.push_back(CreateEntity<Hook>(20.f, 20.f, sf::Color::Yellow));
	   m_hooks[i]->SetPosition(400.f - i * 100, 200.f + i * 100);
   }
	m_Platforms.push_back(CreateEntity<Platform>(200, 50, sf::Color::Blue));
	m_Platforms[0]->SetPosition(500, 550);
	m_Platforms[0]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<BreakablePlatform>(100, 35, sf::Color::Cyan));
	m_Platforms[1]->SetPosition(100, 101);
	m_Platforms[1]->SetRigidBody(true);
	

	//AM.InitTextureInDirectory("coeur.png");
	m_UI.push_back(CreateEntity<Entity>(AM.LoadSprite("coeur"), sf::Color::White));
	m_UI[0]->SetPosition(m_player->GetPosition().x, m_player->GetPosition().y, 0.0F, 0.0F);
	//m_UI[0]->SetSprite(AM.LoadSprite("coeur.png",0,0,26,22));


}

void SampleScene::OnEvent(const sf::Event& event)
{
    InputManager& im = InputManager::Get();

	if (im.IsKeyPressed(sf::Keyboard::E))
	{
		m_player->TakeDamage(1);
	}

	if (im.IsKeyPressed(sf::Keyboard::A))
	{
		m_player->Heal(1);
	}

	m_player->Actions();

}

void SampleScene::OnUpdate()
{
	float dt = GetDeltaTime();

	float j = mCamera->GetView()->getCenter().x - (mCamera->GetView()->getCenter().x / 2) + 10;

	

	m_UI[0]->SetPosition(j, m_player->GetPosition().y - 300, 0.0F, 0.0F);
	GetGameManager()->RefreshCamera(mCamera);


  /*  if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }*/

	IncreaseTimer();
	// for (auto* p : m_Platforms)
	// {
	// 	p->OnUpdate();
	// }
}

void SampleScene::TrySetSelectedEntity(Entity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	/*pEntitySelected = pEntity;*/
}

bool SampleScene::IsAttackTimingOkay()
{
	if (test_timerAttaque >= test_tempsEntreLesAttaque - m_pityFrames / 60.f || test_timerAttaque <= m_pityFrames / 60.F)
	{
		return true;
	}
		
	return false;
}

void SampleScene::IncreaseTimer()
{
	test_timerAttaque += GetDeltaTime();

	if (test_timerAttaque >= test_tempsEntreLesAttaque)
	{
		test_timerAttaque = 0;
	}

}
