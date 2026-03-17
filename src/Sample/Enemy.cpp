#include "Enemy.h"
#include "Utils.h"
#include <iostream>

void Enemy::Initialize()
{
    m_startPos = GetPosition();
}

void Enemy::Update(float dt)
{
    if (!m_isAlive)
        return;

    float move = m_speed * m_direction * dt;

    sf::Vector2f pos = GetPosition();
    SetPosition(pos.x + move, pos.y);

    float dist = Utils::GetDistance(GetPosition().x, 0, m_startPos.x, 0);

    if (dist >= m_maxDistance)
        m_direction *= -1;
}

float Enemy::TakeDamage(int amount)
{
    if (!m_isAlive)
        return 0;

    m_Hpmax -= amount;

    std::cout << "Enemy takes " << amount << " damage. HP = " << m_Hpmax << std::endl;

    if (m_Hpmax <= 0)
    {
        m_isAlive = false;
        std::cout << "Enemy died" << std::endl;
        Destroy();
    }

    return m_Hpmax;
}

void Enemy::Attack()
{
   
}
