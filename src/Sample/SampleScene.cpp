#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"
#include "DummyEntity.h"

#include"Enemy.h"
#include"Mob1.h"
#include"Mob2.h"

#include"Utils.h"

#include"Platform.h"
#include"BreakablePlatform.h"

#include"Entity.h"

#include "Debug.h"
#include "InputManager.h"

#define MAX_JOYSTICK_POS  100
#define MIN_JOYSTICK_POS -100


void SampleScene::OnInitialize()
{
	m_Platforms.push_back(CreateEntity<Platform>(200, 50, sf::Color::Blue));
    m_Platforms[0]->SetPosition(500, 550);
	m_Platforms[0]->SetRigidBody(true);
    
	m_Platforms.push_back(CreateEntity<BreakablePlatform>(100, 35, sf::Color::Cyan));
	m_Platforms[1]->SetPosition(200, 201);
	m_Platforms[1]->SetRigidBody(true);

    SpawnEnemy(200, 170);

	pEntitySelected = nullptr;
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

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
}

void SampleScene::OnUpdate()
{
	float dt = GetDeltaTime();

	for (auto* p : m_Platforms)
	{
		p->OnUpdate();
	}

	for (auto* e : m_enemy)
	{
		e->OnUpdate();
	}
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


