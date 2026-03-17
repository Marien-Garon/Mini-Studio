#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include"Enemy.h"
#include"Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"


void SampleScene::OnInitialize()
{
    AssetManager& AM = AssetManager::getInstance();

	/*pEntity1 = CreateEntity<Enemy>(AM.LoadSprite("sheet", 0, 0, 460, 600), sf::Color::Red);
    pEntity1->SetSpriteScale(0.5f, 0.5f);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);
	pEntity1->SetMoveAble(true);
	pEntity1->SetTag(1);

	pEntity2 = CreateEntity<Enemy>(50,50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);
	pEntity2->SetMoveAble(true);*/

   mCamera = CreateEntity<Camera>(0, 0, sf::Color::Black);
   mCamera->SetupCamera(3, m_player);
   /*CAMERA SPEED HERE*/

   for (int i = 0; i < 3; i++) {
	   m_hooks.push_back(CreateEntity<Hook>(20.f, 20.f, sf::Color::Yellow));
	   m_hooks[i]->SetPosition(400.f - i * 100, 200.f + i * 100);
   }

	m_Platforms.push_back(CreateEntity<BreakablePlatform>(200, 50, sf::Color::Cyan));
	m_Platforms[0]->SetPosition(0,50);
	m_Platforms[0]->SetRigidBody(true);
    
	m_Platforms.push_back(CreateEntity<Platform>(100, 35, sf::Color::Cyan));
	m_Platforms[1]->SetPosition(m_Platforms[0]->GetPosition().x + m_Platforms[0]->GetSize().x, 50);
	m_Platforms[1]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<Platform>(100, 35, sf::Color::Cyan));
	m_Platforms[2]->SetPosition(m_Platforms[1]->GetPosition().x + m_Platforms[1]->GetSize().x, 50);
	m_Platforms[2]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<Platform>(100, 35, sf::Color::Cyan));
	m_Platforms[3]->SetPosition(m_Platforms[2]->GetPosition().x + m_Platforms[2]->GetSize().x, 50);
	m_Platforms[3]->SetRigidBody(true);

	m_Platforms.push_back(CreateEntity<Platform>(100, 35, sf::Color::Cyan));
	m_Platforms[4]->SetPosition(m_Platforms[3]->GetPosition().x + m_Platforms[3]->GetSize().x, 50);
	m_Platforms[4]->SetRigidBody(true);


    SpawnEnemy(200, 170);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
	float dt = GetDeltaTime();
    InputManager& im = InputManager::Get();

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		m_player->TakeDamage(1);
	}

}

	m_player->Actions();
}

void SampleScene::OnUpdate()
{
    float dt = GetDeltaTime();


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
    }
}

void SampleScene::TrySetSelectedEntity(Entity* pEntity, int x, int y)
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