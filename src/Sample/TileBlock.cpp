#include "TileBlock.h"

bool TileBlock::IsSameTile(TileBlock* _tile)
{
	return _tile->GetSpriteData()->textureID == GetSpriteData()->textureID;
}

void TileBlock::OnUpdate()
{
}

void TileBlock::OnCollision(Entity* collidedWith)
{
}

//Herited from platform now
void TileBlock::OnInitialize()
{
	SetMoveAble(false);
	SetRigidBody(true);
}

void TileBlock::OnDestroy()
{
}

Entity* TileBlock::Clone()
{
	AssetManager& am = AssetManager::getInstance();

	TileBlock* newEntity = nullptr;

	int w = m_sprite->data->spritesheet ? m_sprite->data->frameSizeW : m_sprite->data->sizeW;
	int h = m_sprite->data->spritesheet ? m_sprite->data->frameSizeH : m_sprite->data->sizeH;

	newEntity = CreateEntity<TileBlock>(am.CreateTile(m_sprite->textureID));
	newEntity->SetScale(m_sprite->sprite->getScale().x, m_sprite->sprite->getScale().y);
	newEntity->SetSpriteRotation(m_sprite->sprite->getRotation());

	newEntity->SetTag(mTag);
	newEntity->SetMoveAble(m_isMoveable);
	newEntity->SetRigidBody(mRigidBody);

	return newEntity;
	//return CreateClonedEntity<TileBlock>();
}
