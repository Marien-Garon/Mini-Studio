#include "Companion.h"
#include "SampleScene.h"
#include <iostream>

void Companion::OnUpdate()
{
	Follow();

	GetShape()->setFillColor(sf::Color::Blue);

	if (static_cast<SampleScene*>(GetScene())->IsAttackTimingOkay())
		GetShape()->setFillColor(sf::Color::Red);
}

void Companion::OnInitialize()
{
	SetSpeed(2000.f);
}

void Companion::OnCollision(Entity* other)
{
	/*std::cout << "Companion::OnCollision" << std::endl;*/
}

void Companion::Follow()
{
	sf::Vector2f pos = mOwner->GetPosition();

	GoToPosition(pos.x - 150.f, pos.y - 150.f);
}

void Companion::SetOwner(Player* owner)
{
	mOwner = owner;
}
