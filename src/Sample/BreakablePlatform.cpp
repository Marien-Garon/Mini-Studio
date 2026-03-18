#include "BreakablePlatform.h"
#include<iostream>


void BreakablePlatform::OnCollision(Entity* entity)
{
	if (GetCollidingSide(entity) == Side::UP)
	{
	    m_timer -= GetDeltaTime();

		if (m_timer <= 0.5f)

		if (entity->IsTag(1))
		{
			if (GetCollidingSide(entity) == Side::UP)

			{

				m_timer -= GetDeltaTime();

				if (0.f < m_timer <= 0.5f)
				{
					mShape.setFillColor(sf::Color(255 / m_timer, 0, 0, 255));
				}

				if (m_timer <= 0.f && IsRigidBody())
				{
					SetRigidBody(false);
					entity->StartGravity(0);
				}
			}
		}
	}
	
}

void BreakablePlatform::OnInitialize()
{
	SetTag(12);
}
