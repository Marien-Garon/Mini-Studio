#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
    int m_Hpmax = 50;
    int m_damage = 10;
    int m_direction = 1;

    float m_speed = 100.f;
    float m_maxDistance = 200.f;
    float m_attackCooldown = 3.0f;   
    float m_attackTimer = 0.0f;

    bool m_isAlive = true;

    sf::Vector2f m_startPos;
protected:
    void UpdateMovementAndTimers();

public:
    
    void Initialize();
    void OnUpdate() override;

    float TakeDamage(int amount);


    virtual void Attack();
};
