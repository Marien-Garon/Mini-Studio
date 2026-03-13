#include "BreakablePlatform.h"
#include<iostream>


void BreakablePlatform::OnCollision(Entity* entity)
{
	std::cout << "Side = " << (int)GetCollidingSide(entity) << std::endl;
	std::cout << mShape.getPosition().x << "/" << mShape.getPosition().y << std::endl;
	std::cout << entity->GetShape()->getPosition().x << "/" << entity->GetShape()->getPosition().y + entity->GetShape()->getGlobalBounds().height << std::endl;

	if (GetCollidingSide(entity) == Side::UP)
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
