#include "Enemy.h"
#include "Utils.h"
#include<iostream>

void Enemy::Initialize()
{
    m_startPos = GetPosition();
}

void Enemy::OnUpdate(float dt)
{
    float move = m_speed * m_direction * dt;

    sf::Vector2f pos = GetPosition();
    SetPosition(pos.x + move, pos.y);

    float dist = Utils::GetDistance(GetPosition().x, 0, m_startPos.x, 0);

    if (dist >= m_maxDistance)
    {
        m_direction *= -1;
    }
}

float Enemy::TakeDamage(int amount)
{
    if (m_Hpmax <= 0)
    {
        std::cout << "Enemy died" << std::endl;
        EnemyAlive = false;
        Destroy();
    }
    else
    {
        m_Hpmax -= amount;
        std::cout << "Enemy take damage " << std::endl;
        std::cout << "Current Hp: " << m_Hpmax << std::endl;
    }
   
    return m_Hpmax;
}

void Enemy::Attack()
{
    float windowWidth = GetScene()->GetWindowWidth();

    Enemy* attack = CreateEntity<Enemy>(20, 10, sf::Color::Blue);
    attack->SetPosition(GetPosition().x, GetPosition().y);
    attack->GoToDirection(windowWidth * m_directionAttack, GetPosition().y);
}



