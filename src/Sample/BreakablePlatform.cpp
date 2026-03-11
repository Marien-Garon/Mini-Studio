#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(float width, float height, const sf::Color& color)
{
	this->SetRigidBody(true);
	this->SetMoveAble(false);

	IsSteppedOn = false;
	m_timer = m_maxTimer;
}

void BreakablePlatform::OnUpdate(float dt)
{
	if (IsSteppedOn)
	{
		m_timer -= dt;

		if (m_timer <= 0.5f)
		{
			sf::Color::Red;
		}

		if (m_timer <= 0)
		{
			this->Destroy();
		}
	}
}

void BreakablePlatform::OnPlayerContact()
{
	IsSteppedOn = true;
}
