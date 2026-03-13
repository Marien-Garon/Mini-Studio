#include "BreakablePlatform.h"
#include<iostream>


void BreakablePlatform::OnCollision(Entity* player)
{
	std::cout << "Side = " << (int)GetCollidingSide(player) << std::endl;

	if (GetCollidingSide(player) == Side::UP)
	{
	    std::cout << "Timer : " << m_timer << std::endl;

	    m_timer -= GetDeltaTime();

		if (m_timer <= 0.5f)
		{
			mShape.setFillColor(sf::Color(255 / m_timer, 0, 0, 255));
		}

		if (m_timer <= 0.f)
		{
			SetRigidBody(false);
		}
	}
}
