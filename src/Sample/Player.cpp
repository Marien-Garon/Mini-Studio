#include "Player.h"

#include <iostream>

void Player::OnCollision(Entity* other)
{
	std::cout << "Player::OnCollision" << std::endl;
}
