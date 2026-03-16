#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Hook.h"



void SampleScene::OnInitialize()
{
    AssetManager& AM = AssetManager::getInstance();

   m_player= CreateEntity<Player>(50, 50, sf::Color::Red);
   m_player->SetPosition(500, 500);

   m_robot = CreateEntity<Companion>(50, 50, sf::Color::Blue);
   m_robot->SetPosition(m_player->GetPosition().x - 150.f, m_player->GetPosition().y - 150.f);
   m_robot->SetOwner(m_player);

   mCamera = CreateEntity<Camera>(0, 0, sf::Color::Black);
   mCamera->SetupCamera(0, m_player);

   for (int i = 0; i < 3; i++) {
	   m_hooks.push_back(CreateEntity<Hook>(20.f, 20.f, sf::Color::Yellow));
	   m_hooks[i]->SetPosition(400.f - i * 100, 200.f + i * 100);
   }
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

	GetGameManager()->RefreshCamera(mCamera);

  /*  if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }*/

	IncreaseTimer();
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