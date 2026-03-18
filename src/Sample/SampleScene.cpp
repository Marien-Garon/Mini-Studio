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
	m_Platforms.push_back(CreateEntity<Platform>(200, 50, sf::Color::Blue));
    m_Platforms[0]->SetPosition(500, 550);

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

   for (int i = 0; i < 3; i++) {
	   m_hooks.push_back(CreateEntity<Hook>(20.f, 20.f, sf::Color::Yellow));
	   m_hooks[i]->SetPosition(400.f - i * 100, 200.f + i * 100);
   }

	m_Platforms.push_back(CreateEntity<BreakablePlatform>(200, 50, sf::Color::Cyan));
	m_Platforms[0]->SetPosition(500, 550);

	m_Platforms[0]->SetRigidBody(true);
    
	m_Platforms.push_back(CreateEntity<BreakablePlatform>(100, 35, sf::Color::Cyan));
	m_Platforms[1]->SetPosition(200, 201);
	m_Platforms[1]->SetRigidBody(true);


    SpawnEnemy(200, 170);

	pEntitySelected = nullptr;

	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
	m_UI.push_back(CreateEntity<Entity>(AM.CreateSprite("coeur")));
}

void SampleScene::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        
        for (auto* e : m_enemy)
            e->Destroy();

        m_enemy.clear();

        SpawnEnemy(event.mouseButton.x, event.mouseButton.y);
    }

    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
    {
        if (!m_enemy.empty())
        {
            for (int i = 0; i < m_enemy.size(); i++)
            {
                if (m_enemy[i]->TakeDamage(10) <= 0)
                {
                    m_enemy[i]->Destroy();
                    m_enemy.erase(m_enemy.begin() + i);
                    i--; 
                }
            }
        }

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

	m_player->Actions();


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

	// NAN NAN NAN
	//for (auto* p : m_Platforms)
	//{
	//	p->OnUpdate();
	//}

	//for (auto* e : m_enemy)
	//{
	//	e->OnUpdate();
	//}
}

Enemy* SampleScene::SpawnEnemy(int x, int y)
{
	Platform* p1 = m_Platforms[0];
    float px1 = p1->GetTopLeft().x;
    float py1 = p1->GetTopLeft().y;
    float width1 = p1->GetSize().x;
   
    Platform* p2 = m_Platforms[1];
    float px2 = p2->GetTopLeft().x;
    float py2 = p2->GetTopLeft().y;
    float width2 = p2->GetSize().x;

    
    Enemy* mob1 = CreateEntity<Mob1>(50, 30, sf::Color::Red);
    mob1->SetPlatform(p1);
    mob1->SetPosition(px1 + width1 * 0.5f, py1 - 1, 0.5f, 1.f);
    mob1->Initialize();
    m_enemy.push_back(mob1);

    
    Enemy* mob2 = CreateEntity<Mob2>(50, 20, sf::Color::Blue);
    mob2->SetPlatform(p2);
    mob2->SetPosition(px2 + width2 * 0.5f, py2 - 1, 0.5f, 1.f);
    mob2->Initialize();
    m_enemy.push_back(mob2);

    return mob1;
}

void SampleScene::TrySetSelectedEntity(Entity* pEntity, int x, int y)
{
    /*  if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }*/
    
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

