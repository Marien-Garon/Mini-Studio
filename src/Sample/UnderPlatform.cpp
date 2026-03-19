#include "UnderPlatform.h"

void UnderPlatform::OnCollision(Entity* entity)
{
	if (GetCollidingSide(entity) == Side::DOWN) {
		if(entity->GetTag() == 1) entity->SetPosition(entity->GetPosition().x, GetPosition(0.5f, 0.f).y, 0.5f, 1.f);
	}
}

Entity* UnderPlatform::Clone()
{
	AssetManager& am = AssetManager::getInstance();

	UnderPlatform* newEntity = nullptr;

	int w = m_sprite->data->spritesheet ? m_sprite->data->frameSizeW : m_sprite->data->sizeW;
	int h = m_sprite->data->spritesheet ? m_sprite->data->frameSizeH : m_sprite->data->sizeH;

	newEntity = CreateEntity<UnderPlatform>(am.CreateTile(m_sprite->textureID,SpriteType::UnderPlatform));
	newEntity->SetScale(m_sprite->sprite->getScale().x, m_sprite->sprite->getScale().y);
	newEntity->SetSpriteRotation(m_sprite->sprite->getRotation());

	newEntity->SetTag(mTag);
	newEntity->SetMoveAble(m_isMoveable);
	newEntity->SetRigidBody(mRigidBody);

	return newEntity;
}