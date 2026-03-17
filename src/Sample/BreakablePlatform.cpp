#include "BreakablePlatform.h"
#include<iostream>


void BreakablePlatform::OnCollision(Entity* entity)
{
	std::cout << "Side : " << (int)GetCollidingSide(entity);

	if (GetCollidingSide(entity) == Side::UP)
	{
		std::cout << "Timer : "<<m_timer;
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
