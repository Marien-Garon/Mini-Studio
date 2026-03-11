#include "NewEntity.h"

bool NewEntity::IsColliding(NewEntity* other)
{
	return m_collider.IsColliding(other->GetCollider());
}

bool NewEntity::IsInside(float _x, float _y)
{
	return m_collider.IsInside(_x, _y);
}


bool NewEntity::IsInside(NewEntity* _other)
{
	return m_collider.IsInside(_other->GetCollider());
}

Side NewEntity::GetCollidingSide(NewEntity* _other)
{
	return m_collider.GetCollisionSide(_other->GetCollider());
}

void NewEntity::Update()
{
	OnUpdate();
}

void NewEntity::Initialize()
{
	OnInitialize():
}
