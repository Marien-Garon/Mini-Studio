#include "Companion.h"

#include <iostream>

void Companion::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}