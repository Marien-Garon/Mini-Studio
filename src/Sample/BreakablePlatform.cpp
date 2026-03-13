#include "BreakablePlatform.h"
#include<iostream>

void BreakablePlatform::OnCollision(Entity* player)
{
	while (isSteppedOn)
	{
		if (GetCollidingSide(player) == Side::UP)
		{
			std::cout << "Timer : " << m_timer << std::endl;

			m_timer -= 0.2f;

			if (m_timer <= 0.5f)
			{
				
				mShape.setFillColor(sf::Color(255 / m_timer, 0, 0, 255));
			}

			if (m_timer == 0)
			{
				SetRigidBody(false);
			}
		}
	}
}
