#include "DecoBlock.h"

Entity* DecoBlock::Clone()
{
	AssetManager& am = AssetManager::getInstance();

	DecoBlock* newEntity = nullptr;

	int w = m_sprite->data->spritesheet ? m_sprite->data->frameSizeW : m_sprite->data->sizeW;
	int h = m_sprite->data->spritesheet ? m_sprite->data->frameSizeH : m_sprite->data->sizeH;

	newEntity = CreateEntity<DecoBlock>(am.CreateTile(m_sprite->textureID,SpriteType::DecoBlock));
	newEntity->SetScale(m_sprite->sprite->getScale().x, m_sprite->sprite->getScale().y);
	newEntity->SetSpriteRotation(m_sprite->sprite->getRotation());

	newEntity->SetTag(mTag);
	newEntity->SetMoveAble(m_isMoveable);
	newEntity->SetRigidBody(mRigidBody);

	return newEntity;
}
