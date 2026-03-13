#include "DummyEntity.h"

#include <iostream>

void DummyEntity::OnCollision(Entity* other)
{
	//std::cout << "DummyEntity::OnCollision" << std::endl;

	if (mTag == 1)
	{
		if (GetCollidingSide(other) == Side::RIGHT)
			std::cout << "Collision Right" << std::endl;

		if (GetCollidingSide(other) == Side::LEFT)
			std::cout << "Collision Left" << std::endl;

		if (GetCollidingSide(other) == Side::UP)
			std::cout << "Collision Up" << std::endl;

		if (GetCollidingSide(other) == Side::DOWN)
			std::cout << "Collision Down" << std::endl;

		if (GetCollidingSide(other) == Side::INSIDE)
			std::cout << "Inside" << std::endl;

		if (GetCollidingSide(other) == Side::NONE)
			std::cout << "None" << std::endl;
	}
}