#pragma once
#include "PhysicalEntity.h"

class Enemy : public PhysicalEntity
{
private:
    int m_Hpmax = 1;
    int m_damage = 1;

    bool EnemyAlive = true;
      
    float m_maxDistance = 200.f; 
    sf::Vector2f m_startPos;     

public:
    void OnInitialize() override;
    void OnUpdate() override;

    float TakeDamage(int amount);
};
