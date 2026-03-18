#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private:
    sf::Vector2f m_direction = { 0.f, 0.f };
    float m_speed = 300.f;
    bool m_isAlive = true;

public:
    void SetDirection(float dx, float dy, float speed);

    void OnInitialize() override;
	void OnUpdate() override;

    void DestroyBullet();
};