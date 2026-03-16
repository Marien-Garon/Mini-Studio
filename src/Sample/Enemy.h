#pragma once
#include "PhysicalEntity.h"

class Enemy : public PhysicalEntity
{
private:
    int m_Hpmax = 50;
    int m_damage;

    bool EnemyAlive = true;

    float m_speed = 100.f;       
    int m_direction = 1;         
    float m_maxDistance = 200.f; 
    sf::Vector2f m_startPos;     

public:
    void Initialize();           
    void OnUpdate(float dt);

    float TakeDamage(int amount);
    void Attack();
};
