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
	}
}

bool Grapple::AsReachedTarget()
{

	if (GetPosition().x == mTarget.position.x && GetPosition().y == mTarget.position.y)
		return true;

	return false;
}

