#include "Mob2.h"

#include "Enemy.h"

void Mob2::OnInitialize()
{
    SetName("Mob2");
    m_Hpmax = 80;
    m_speed = 70.f;
}

void Mob2::Attack()
{
    if (!m_isAlive)
        return;

    sf::Vector2f pos = GetPosition();

    // Projectile 1 : tout droit
    {
        Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f, 0.f, 400.f);
    }

    // Projectile 2 : diagonale haut
    {
        Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f, -0.5f, 400.f);
    }

    // Projectile 3 : diagonale bas
    {
        Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f, 0.5f, 400.f);
    }
}




