#include "ClassicPlatform.h"

ClassicPlatform::ClassicPlatform(float width, float height, const sf::Color& color)
{
	this->SetRigidBody(true);
	this->SetMoveAble(false);
}

void ClassicPlatform::OnUpdate(float dt)
{
}

void ClassicPlatform::OnPlayerContact()
{
}
