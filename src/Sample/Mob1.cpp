
#include "Mob1.h"

void Mob1::Attack()
{
    float windowWidth = GetScene()->GetWindowWidth();

    Entity* bullet = CreateEntity<Entity>(10, 10, sf::Color::Yellow);
    bullet->SetPosition(GetPosition().x, GetPosition().y);

    bullet->GoToDirection(windowWidth, GetPosition().y, 400.f);
}
