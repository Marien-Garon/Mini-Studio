#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"
#include "Button.h"
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
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

			if (m_buttonContinue && m_buttonContinue->IsInside(mousePos.x, mousePos.y))
				m_buttonContinue->Click();

			if (m_buttonRestart && m_buttonRestart->IsInside(mousePos.x, mousePos.y))
				m_buttonRestart->Click();

			if (m_buttonExit && m_buttonExit->IsInside(mousePos.x, mousePos.y))
				m_buttonExit->Click();
		}
		return;
	}

	float dt = GetDeltaTime();
	InputManager& im = InputManager::Get();

	if (event.mouseButton.button == sf::Mouse::Button::Left)
		m_player->TakeDamage(1);

	if (event.mouseButton.button == sf::Mouse::Button::Right)
		m_player->Heal(1);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		SetPause();

	m_player->Actions();

}

void SampleScene::OnUpdate()
{
	if (m_shouldRestart)
	{
		m_shouldRestart = false;
		GameManager::Get()->ClearCurrentSceneEntities();
		m_UI.clear();
		m_Platforms.clear();
		m_hooks.clear();
		m_player = nullptr;
		m_robot = nullptr;
		mCamera = nullptr;

		if (m_pauseMenu) { m_pauseMenu->Destroy(); m_pauseMenu = nullptr; }
		if (m_buttonContinue) { m_buttonContinue->Destroy(); m_buttonContinue = nullptr; }
		if (m_buttonRestart) { m_buttonRestart->Destroy(); m_buttonRestart = nullptr; }
		if (m_buttonSettings) { m_buttonSettings->Destroy(); m_buttonSettings = nullptr; }
		if (m_buttonExit) { m_buttonExit->Destroy(); m_buttonExit = nullptr; }

		OnInitialize();

		return;
	}

	if (mIsPaused) {
		GameManager* gm = GameManager::Get();
		if (!gm) return;

		gm->SetFixedView();

		float winW = static_cast<float>(GetWindowWidth());
		float winH = static_cast<float>(GetWindowHeight());

		float centerX = winW / 2.f;
		float centerY = winH / 2.f;

		if (m_pauseMenu && m_pauseMenu->GetSprite() && m_pauseMenu->GetSprite()->getTexture())
		{
			sf::Sprite* sprite = m_pauseMenu->GetSprite();
			sf::Vector2u texSize = sprite->getTexture()->getSize();
			float winW = static_cast<float>(GameManager::Get()->GetWindow()->getSize().x);
			float winH = static_cast<float>(GameManager::Get()->GetWindow()->getSize().y);
			sprite->setScale(winW / float(texSize.x), winH / float(texSize.y));
			sprite->setPosition(winW / 2.f - sprite->getGlobalBounds().width / 2.f,
				winH / 2.f - sprite->getGlobalBounds().height / 2.f);
		}

		if (m_buttonContinue)
			m_buttonContinue->SetPosition((GetWindowWidth() / 2) + 650.f, (GetWindowHeight() / 2) + 700.f);

		if (m_buttonRestart)
			m_buttonRestart->SetPosition((GetWindowWidth() / 2) + 1000.f, (GetWindowHeight() / 2) + 700.f);

		if (m_buttonSettings)
			m_buttonSettings->SetPosition((GetWindowWidth() / 2) + 650.f, (GetWindowHeight() / 2) + 800.f);

		if (m_buttonExit)
			m_buttonExit->SetPosition((GetWindowWidth() / 2) + 1000.f, (GetWindowHeight() / 2) + 800.f);
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
	m_pauseMenu = CreateEntity<Entity>(AM.LoadSprite("pause"), sf::Color::Transparent);
	m_pauseMenu->SetSpriteScale(1, 1);

	m_buttonContinue = CreateEntity<Button>(AM.LoadSprite("boutoncontinue"), sf::Color::Transparent);
	m_buttonContinue->SetSpriteScale(0.9, 0.9);

	m_buttonRestart = CreateEntity<Button>(AM.LoadSprite("boutonrestart"), sf::Color::Transparent);
	m_buttonRestart->SetSpriteScale(0.9, 0.9);

	m_buttonSettings = CreateEntity<Button>(AM.LoadSprite("boutonsettings"), sf::Color::Transparent);
	m_buttonSettings->SetSpriteScale(0.9, 0.9);

	m_buttonExit = CreateEntity<Button>(AM.LoadSprite("boutonrexit"), sf::Color::Transparent);
	m_buttonExit->SetSpriteScale(0.9, 0.9);

	if (m_buttonContinue)
		m_buttonContinue->SetFunction([this]() { this->UnPause(); });

}

void SampleScene::UnPause()
{
	mIsPaused = false;
	m_player->SetSpeed(300.f);
	m_player->StartGravity(0.f);
	m_robot->SetSpeed(2000.f);
	//parallaxe->Start()
	mCamera->SetSpeed(3.f);

	if (m_pauseMenu) m_pauseMenu->Destroy();
	if (m_buttonContinue) m_buttonContinue->Destroy();
	if (m_buttonRestart) m_buttonRestart->Destroy();
	if (m_buttonSettings) m_buttonSettings->Destroy();
	if (m_buttonExit) m_buttonExit->Destroy();
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
