
#include "Mob1.h"

void Mob1::Attack()
{
	float windowWidth = GetScene()->GetWindowWidth();

	Mob1* mob1 = CreateEntity<Mob1>(20, 30, sf::Color::Red);
	mob1->SetPosition(GetPosition().x, GetPosition().y);
	mob1->GoToDirection(windowWidth, GetPosition().y);
}
