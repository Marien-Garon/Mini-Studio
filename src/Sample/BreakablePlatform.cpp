#include "BreakablePlatform.h"
#include<iostream>
#include "SampleScene.h"


void BreakablePlatform::OnCollision(Entity* entity)
{
	std::cout << IsRigidBody() << std::endl;
	if (entity->IsTag(1))
	{
		if (GetCollidingSide(entity) == Side::UP)
		{
			if(GetScene<SampleScene>()->mIsPaused) {
				return;
			}

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
