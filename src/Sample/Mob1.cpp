#include "Mob1.h"
#include "Bullet.h"

void Mob1::Attack()
{
    Bullet* bullet = CreateEntity<Bullet>(10, 10, sf::Color::Yellow);
    bullet->SetPosition(GetPosition().x, GetPosition().y);
    bullet->SetDirection(m_directionFacing, 0.f);
}
