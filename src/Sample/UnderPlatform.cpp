#include "UnderPlatform.h"

void UnderPlatform::OnCollision(Entity* entity)
{
	if (GetCollidingSide(entity) == Side::DOWN) {
		entity->SetPosition(entity->GetPosition().x, GetPosition(0.5f, 0.f).y, 0.5f, 1.f);
	}
}
