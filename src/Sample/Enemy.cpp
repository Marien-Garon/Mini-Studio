#include "Enemy.h"
#include "Utils.h"
#include<iostream>

void Enemy::OnInitialize()
{
    m_startPos = GetPosition();
}



void Enemy::OnUpdate()
{
    if (EnemyAlive == false)
          Destroy();
}

float Enemy::TakeDamage(int amount)
{
    m_Hpmax -= amount;

    if (m_Hpmax == 0)
    {
        std::cout << "Enemy died" << std::endl;
        EnemyAlive = false;
    }
    else
    {
        std::cout << "Enemy take damage " << std::endl;
        std::cout << "Current Hp :  " << m_Hpmax << std::endl;
    }
   
    return m_Hpmax;
}
