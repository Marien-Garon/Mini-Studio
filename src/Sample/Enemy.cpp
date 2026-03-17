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

    float width = GetScene()->GetWindowWidth();
    float height = GetScene()->GetWindowHeight();

    sf::Vector2f pos1 = GetPosition();

    if (pos1.x < -20 || pos1.x > width + 20 ||
        pos1.y < -20 || pos1.y > height + 20)
    {
        Destroy();
    }

    float dist = Utils::GetDistance(GetPosition().x, 0, m_startPos.x, 0);

    if (dist >= m_maxDistance)
        m_direction *= -1;
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
