#include "SampleScene.h"
#include <iostream>
#include "PhysicalEntity.h"
#include "DummyEntity.h"
#include"Enemy.h"
#include"Mob1.h"
#include"Utils.h"
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
        {
            e->Destroy();
        }
           
        m_enemy.clear();

        SpawnEnemy(event.mouseButton.x, event.mouseButton.y);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!m_enemy.empty())
            m_enemy[0]->TakeDamage(10);
    }
    
    for (auto* e : m_enemy)
        e->Attack();
}

void SampleScene::OnUpdate()
{
    float dt = GetDeltaTime();

    if (!m_enemy.empty())
        m_enemy[0]->Update(dt);

    if (pEntitySelected != nullptr)
    {
        sf::Vector2f position = pEntitySelected->GetPosition();
        Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
    }
}

Enemy* SampleScene::SpawnEnemy(int x, int y)
{
    Enemy* e = CreateEntity<Enemy>(50,30, sf::Color::Red);
    e->SetPosition(x, y);
    e->Initialize();

    m_enemy.push_back(e);
    return e;
}

