#include "Companion.h"

#include <iostream>

void Companion::OnUpdate()
{
}

void Companion::OnInitialize()
{
	SetSpeed(2000.f);
}

void Companion::OnCollision(Entity* other)
{
	std::cout << "Companion::OnCollision" << std::endl;
}

void Companion::Follow(Player* _player)
{
	sf::Vector2f pos = _player->GetPosition();

	GoToPosition(pos.x - 150.f, pos.y - 150.f);
}
