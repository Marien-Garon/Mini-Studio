#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"
#include "DummyEntity.h"
#include "Enemy.h"
#include "Mob1.h"
#include "Mob2.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"

void SampleScene::OnInitialize()
{
    SpawnEnemy(600, 600);
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

    
    for (auto* e : m_enemy)
        e->OnUpdate();

    
    if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }
}

Enemy* SampleScene::SpawnEnemy(int x, int y)
{
   
    Enemy* mob1 = CreateEntity<Mob1>(50, 30, sf::Color::Red);
    mob1->SetPosition(x, y);
    mob1->Initialize();
    m_enemy.push_back(mob1);


    Enemy* mob2 = CreateEntity<Mob2>(50, 20, sf::Color::Blue);
    mob2->SetPosition(x + 90, y - 80); 
    mob2->Initialize();
    m_enemy.push_back(mob2);

    return mob1; 
}
