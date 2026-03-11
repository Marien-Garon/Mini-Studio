#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(float width, float height, const sf::Color& color)
{
	this->SetRigidBody(true);
	this->SetMoveAble(false);

	collider.width = width;
	collider.height = height;

	IsSteppedOn = false;
	m_timer = 2.0f;
}

void BreakablePlatform::OnUpdate(float dt)
{

	if (IsBroken) return;

	//1. On synchronise toujours le collider avec la position actuelle
	collider.SetPosition(this->GetPosition().x, this->GetPosition().y);

	// 2. Si le joueur a touché la plateforme, on réduit le temps
	if (IsSteppedOn)
	{
		m_timer -= dt;

		if (m_timer <= 0.5f)
		{
			sf::Color::Red;
		}

		// 3. Si le temps est écoulé, on detruit tout
		if (m_timer <= 0)
		{
			this->Destroy();
		}
	}
}

void BreakablePlatform::CheckCollision(AABBCollider& playerCollider, PhysicalEntity* player)
{
	if (IsBroken) return;

	if(collider.IsColliding(playerCollider))
	{ 
		Side side = collider.GetCollisionSide(playerCollider);

		if (side == Side::UP)
		{

			IsSteppedOn = true;

			// On stabilise le joueur sur la plateforme
			player->SetPosition(player->GetPosition().x, collider.y - playerCollider.height);
			player->StopFall();
			OnPlayerContact();
		}
	}

}

void BreakablePlatform::OnPlayerContact()
{
	IsSteppedOn = true;
}
