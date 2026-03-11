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


