#include "Mob1.h"

void Mob1::OnInitialize()
{
    m_attackTimer = 0.f;   
}

void Mob1::Attack()
{
    if (!m_isAlive)
        return;

    float windowWidth = GetScene()->GetWindowWidth();

    Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Yellow);
    bullet->SetPosition(GetPosition().x, GetPosition().y);
    bullet->GoToDirection(windowWidth, GetPosition().y, 400.f);
}
