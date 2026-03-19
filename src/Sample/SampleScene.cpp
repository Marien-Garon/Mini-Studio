#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"

#include"Enemy.h"
#include"Mob1.h"
#include"Mob2.h"

#include"Utils.h"

#include "InputManager.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Hook.h"

#include"Platform.h"
#include"BreakablePlatform.h"
#include"Entity.h"
#include "Debug.h"
#include "LevelEditor.h"

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100


void SampleScene::OnInitialize()
{

    AssetManager& AM = AssetManager::getInstance();
	m_parallaxe = CreateEntity<Parallaxe>(0, 0, sf::Color::Black);
	m_parallaxe->Start();

	//std::vector<Entity*> test = LevelEditor::LoadLevel(this, "Level0");

	m_player= CreateEntity<Player>(50, 50, sf::Color::Red);
	m_player->SetPosition(0, 0);

	m_robot = CreateEntity<Companion>(50, 50, sf::Color::Blue);
	m_robot->SetPosition(m_player->GetPosition().x - 150.f, m_player->GetPosition().y - 150.f);
	m_robot->SetOwner(m_player);

   mCamera = CreateEntity<Camera>(0, 0, sf::Color::Black);
   mCamera->SetupCamera(0, m_player);
   /*CAMERA SPEED HERE*/

  
	m_Platforms.push_back(CreateEntity<Platform>(1000, 50, sf::Color::Blue));
	m_Platforms[0]->SetPosition(0, 10);
	m_Platforms[0]->SetRigidBody(true);

	Mob1* Test = CreateEntity<Mob1>(AM.CreateSprite("Mob1Animation", 0, 0, 1085, 1440));
	Test->SetScale(0.05, 0.05);
	Test->SetPosition(100, 0, 0.f, 0.f);
	Test->SetRigidBody(true);
	Test->PlayAnimation("walkRight");

   


	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
}

void SampleScene::OnEvent(const sf::Event& event)
{

	float dt = GetDeltaTime();
    InputManager& im = InputManager::Get();

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		m_player->TakeDamage(1);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		m_player->Heal(1);
	}


}

void SampleScene::OnUpdate()
{
	float i = mCamera->GetView()->getCenter().y - (GetWindowHeight() / 2);
	float j = mCamera->GetView()->getCenter().x - (GetWindowWidth() / 2);

	switch (m_player->GetHealth())
	{
	case(3):
		m_UI[0]->SetPosition(j, i, 0.0F, 0.0F);
		m_UI[1]->SetPosition(j + 30, i, 0.0F, 0.0F);
		m_UI[1]->SetSpriteColor(sf::Color::White);

		m_UI[2]->SetPosition(j + 60, i, 0.0F, 0.0F);
		m_UI[2]->SetSpriteColor(sf::Color::White);
		break;

	case(2):
		m_UI[0]->SetPosition(j, i, 0.0F, 0.0F);
		m_UI[1]->SetPosition(j + 30, i, 0.0F, 0.0F);
		m_UI[1]->SetSpriteColor(sf::Color::White);

		m_UI[2]->SetSpriteColor(sf::Color::Transparent);
		break;
	case(1):
		m_UI[0]->SetPosition(j, i, 0.0F, 0.0F);
		m_UI[1]->SetSpriteColor(sf::Color::Transparent);
		m_UI[2]->SetSpriteColor(sf::Color::Transparent);
		break;


	}

	GetGameManager()->RefreshCamera(mCamera);

	IncreaseTimer();

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

Camera* SampleScene::GetCamera() const
{
	return mCamera;
}

