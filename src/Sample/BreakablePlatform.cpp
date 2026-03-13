#include "BreakablePlatform.h"
#include<iostream>

void BreakablePlatform::OnCollision(Entity* player)
{
	if (!isBroken) return;

	if (GetCollidingSide(player) == Side::UP)
	{
		if (isSteppedOn)
		{
			isSteppedOn = true;

			m_timer -= 0.2f;

			if (m_timer <= 0.5f)
			{
				std::cout << m_timer << std::endl;
				mShape.setFillColor(sf::Color(255 / m_timer, 0, 0, 255));
			}

			if (m_timer == 0)
			{
				SetRigidBody(false);
			}
		}
	}
}
