#include "Grapple.h"
#include "Player.h"

void Grapple::OnInitialize()
{
	SetSpeed(200.f);
}

void Grapple::OnUpdate()
{
	if (AsReachedTarget()) {
		m_Owner->GoToPosition(GetPosition().x, GetPosition().y);
		m_Owner->m_isTravelling = false;
	}
}

bool Grapple::AsReachedTarget()
{

	if (GetPosition().x == mTarget.position.x && GetPosition().y == mTarget.position.y)
	{
		m_Owner->StopGravity();
		return true;
	}

	return false;
}

