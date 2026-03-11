#include "ClassicPlatform.h"
#include "PhysicalEntity.h"

ClassicPlatform::ClassicPlatform(float width, float height, const sf::Color& color)
{
	this->SetRigidBody(true);
	this->SetMoveAble(false);

    collider.width = width;
    collider.height = height;
}


void ClassicPlatform::CheckCollision(AABBCollider& playerCollider, PhysicalEntity* player)
{
    if (collider.IsColliding(playerCollider))
    {
        Side side = collider.GetCollisionSide(playerCollider);

        if (side == Side::UP)
        {
            // On stabilise le joueur sur la plateforme
            player->SetPosition(player->GetPosition().x, collider.y - playerCollider.height);
            player->StopFall();
        }
    }
}

void ClassicPlatform::OnUpdate(float dt)
{
    collider.SetPosition(this->GetPosition().x,this->GetPosition().y);
}

void ClassicPlatform::OnPlayerContact()
{
}
