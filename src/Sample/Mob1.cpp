#include "Mob1.h"

void Mob1::OnInitialize()
{
    SetName("Mob1");
    m_Hpmax = 30;
    m_speed = 150.f;  
}

void Mob1::Attack()
{
    if (!m_isAlive)
        return;

    float windowWidth = GetScene()->GetWindowWidth();

    Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Yellow);
    bullet->SetPosition(GetPosition().x, GetPosition().y);
    bullet->GoToDirection(windowWidth * m_directionFacing, GetPosition().y, 400.f);
}
