#include "Mob1.h"
#include "Bullet.h"

void Mob1::OnInitialize()
{
    SetName("Mob1");
    m_Hpmax = 30;
    m_speed = 150.f;  
}

//TO DO ATTACK when player is detected
void Mob1::Attack()
{
    if (!m_isAlive)
        return;

    float windowWidth = GetScene()->GetWindowWidth();

    Bullet* bullet = CreateEntity<Bullet>(10, 10, sf::Color::Yellow);
    bullet->SetPosition(GetPosition().x, GetPosition().y);
    bullet->SetDirection(m_directionFacing, 0.f, 400.f);
}
