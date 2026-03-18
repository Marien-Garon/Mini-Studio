#include "Enemy.h"
#include "Utils.h"
#include <iostream>

void Enemy::UpdateMovementAndTimers()
{
    float dt = GetDeltaTime();

    m_attackTimer += dt;

    float move = m_speed * m_direction * dt;
    sf::Vector2f pos = GetPosition();
    SetPosition(pos.x + move, pos.y);

   
    if (m_platform != nullptr)
    {
        float left = m_platform->GetTopLeft().x;
        float right = left + m_platform->GetSize().x;

        float enemyLeft = GetPosition(0.f, 0.5f).x;
        float enemyRight = GetPosition(1.f, 0.5f).x;

        if (enemyLeft < left)
            m_direction = 1;

        if (enemyRight > right)
            m_direction = -1;
    }
    
    float width = GetScene()->GetWindowWidth();
    float height = GetScene()->GetWindowHeight();

    sf::Vector2f pos1 = GetPosition();

    if (pos1.x < -20 || pos1.x > width + 20 ||
        pos1.y < -20 || pos1.y > height + 20)
    {
        Destroy();
    }

    if (m_direction > 0)
        m_directionFacing = 1;
    else
        m_directionFacing = -1;

}


void Enemy::Initialize()
{
    m_startPos = GetPosition();
}

void Enemy::OnUpdate()
{
    if (!m_isAlive)
        return;

    UpdateMovementAndTimers();

    if (m_attackTimer >= m_attackCooldown)
    {
        Attack();
        m_attackTimer = 0.f;
    }
}


float Enemy::TakeDamage(int amount)
{
     if (!m_isAlive)
        return 0;

    m_Hpmax -= amount;

    std::cout << m_name << " Take : " << amount << " damage. HP = " << m_Hpmax << std::endl;

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
