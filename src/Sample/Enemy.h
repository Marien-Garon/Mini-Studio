#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    int m_Hpmax = 50;
    int m_damage = 10;
    int m_direction = 1;

    float m_speed = 100.f;
    float m_maxDistance = 200.f;

    bool m_isAlive = true;

    sf::Vector2f m_startPos;

public:
    
    void Initialize();
    void Update(float dt);

    float TakeDamage(int amount);


    virtual void Attack();
};
