#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    int m_Hpmax;
    int m_damage;

    bool EnemyAlive = true;

    float m_speed = 100.f;       
    int m_direction = 1;         
    float m_maxDistance = 200.f; 
    sf::Vector2f m_startPos;     

public:
    void Initialize();           
    void Update(float dt);

    float TakeDamage(int amount);
};
