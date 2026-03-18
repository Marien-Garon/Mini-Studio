#include "Mob2.h"
#include "Bullet.h"
#include "Enemy.h"


void Mob2::Attack()
{

    sf::Vector2f pos = GetPosition();

    // Projectile 1 : tout droit
    {
        Bullet* bullet = CreateEntity<Bullet>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f * m_directionFacing, 0.f);
    }

    // Projectile 2 : diagonale haut
    {
        Bullet* bullet = CreateEntity<Bullet>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f* m_directionFacing, -0.5f);
    }

    // Projectile 3 : diagonale bas
    {
        Bullet* bullet = CreateEntity<Bullet>(10, 10, sf::Color::Cyan);
        bullet->SetPosition(pos.x, pos.y);
        bullet->SetDirection(1.f * m_directionFacing, 0.5f);
    }
}




