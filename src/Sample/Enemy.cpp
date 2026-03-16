#include "Enemy.h"
#include "Utils.h"
#include<iostream>

void Enemy::Initialize()
{
    m_startPos = GetPosition();
}

void Enemy::Update(float dt)
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
    m_Hpmax -= amount;

    if (m_Hpmax <= 0)
    {
        std::cout << "Enemy died" << std::endl;
        EnemyAlive = false;
        Destroy();
    }

    std::cout << "Enemy take damage\n Current Hp: " << m_Hpmax << std::endl;
    return m_Hpmax;
}

float Enemy::Attack(int dmg)
{
    m_damage = dmg;
    
    return m_damage;
}

