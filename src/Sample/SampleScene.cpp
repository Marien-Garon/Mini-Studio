#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"

#include "AssetManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Hook.h"
#include "PauseScene.h"

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

   m_player = CreateEntity<Player>(50, 50, sf::Color::Red);
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
	//m_Platforms.push_back(CreateEntity<Platform>(200, 50, sf::Color::Blue));
	//m_Platforms[0]->SetPosition(500, 550);
	//m_Platforms[0]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<BreakablePlatform>(200, 50, sf::Color::Cyan));
	m_Platforms[0]->SetPosition(500, 550);
	m_Platforms[0]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<BreakablePlatform>(100, 35, sf::Color::Cyan));
	m_Platforms[1]->SetPosition(100, 101);
	m_Platforms[1]->SetRigidBody(true);

	m_UI.push_back(CreateEntity<Entity>(AM.LoadSprite("coeur"), sf::Color::White));
	m_UI.push_back(CreateEntity<Entity>(AM.LoadSprite("coeur"), sf::Color::White));
	m_UI.push_back(CreateEntity<Entity>(AM.LoadSprite("coeur"), sf::Color::White));

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (mIsPaused) {
		GameManager* gm = GameManager::Get();

		if (!gm) return;
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

			if (m_buttonContinue->IsInside(mousePos.x, mousePos.y))
			{
				UnPause();
			}

			if (m_buttonExit && m_buttonExit->IsInside(mousePos.x, mousePos.y))
			{
				if (gm && gm->GetWindow())
					gm->GetWindow()->close();
			}

			if (m_buttonRestart->IsInside(mousePos.x, mousePos.y))
			{
				GameManager::Get()->ClearCurrentSceneEntities();
				OnInitialize();
			}
		}
		return;
	}

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

	if (im.IsKeyPressed(sf::Keyboard::Escape))
	{
		SetPause();
	}
	
	m_player->Actions();

}

void SampleScene::OnUpdate()
{
	if (mIsPaused) {
		GameManager* gm = GameManager::Get();
		if (!gm) return;

		gm->SetFixedView();

		float winW = static_cast<float>(gm->GetWindow()->getSize().x);
		float winH = static_cast<float>(gm->GetWindow()->getSize().y);

		float centerX = winW / 2.f;
		float centerY = winH / 2.f;

		if (m_pauseMenu && m_pauseMenu->HasSprite() && m_pauseMenu->GetSprite())
		{
			sf::Sprite* sprite = m_pauseMenu->GetSprite();
			sf::Vector2u texSize = sprite->getTexture()->getSize();

			float scale = std::min(winW / float(texSize.x), winH / float(texSize.y));
			sprite->setScale(scale, scale);

			sf::FloatRect bounds = sprite->getGlobalBounds();
			sprite->setPosition(centerX - bounds.width / 2.f, centerY - bounds.height / 2.f);
		}

		float btnWidth = 350.f;
		if (m_buttonContinue) m_buttonContinue->SetPosition(centerX - 16, centerY - 60);
		if (m_buttonRestart)  m_buttonRestart->SetPosition(centerX - 16, centerY + 35);
		if (m_buttonSave)     m_buttonSave->SetPosition(centerX - 16, centerY + 128);
		if (m_buttonSettings) m_buttonSettings->SetPosition(centerX - 16, centerY + 222);
		if (m_buttonExit)     m_buttonExit->SetPosition(centerX + 410, centerY + 290);
		return;
	}

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




	GameManager::Get()->RefreshCamera(mCamera);


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

void SampleScene::SetPause()
{
	mIsPaused = true;
	m_player->SetSpeed(0.f);
	m_player->StopGravity();
	m_robot->SetSpeed(0.f);
	//parallaxe->Stop()
	mCamera->SetSpeed(0.f);

	AssetManager& AM = AssetManager::getInstance();
	m_pauseMenu = CreateEntity<Entity>(AM.LoadSprite("pause"), sf::Color::Red);

	m_buttonContinue = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonRestart = CreateEntity<Entity>(350, 65, sf::Color::Transparent);

	m_buttonSave = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonSettings = CreateEntity<Entity>(350, 65, sf::Color::Transparent);
	m_buttonExit = CreateEntity<Entity>(100, 65, sf::Color::Transparent);
}

void SampleScene::UnPause()
{
	mIsPaused = false;
	m_player->SetSpeed(300.f);
	m_player->StartGravity(0.f);
	m_robot->SetSpeed(2000.f);
	//parallaxe->Start()
	mCamera->SetSpeed(3.f);

	m_pauseMenu->Destroy();
	m_buttonContinue->Destroy();
	m_buttonRestart->Destroy();
	m_buttonSave->Destroy();
	m_buttonSettings->Destroy();
	m_buttonExit->Destroy();
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
