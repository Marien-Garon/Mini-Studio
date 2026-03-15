#include "Entity.h"

#include "GameManager.h"
#include <SFML/Graphics/Sprite.hpp>

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::CreateEntity(float width, float height, const sf::Color& color)
{
	return GetScene()->CreateEntity<T>(width, height, color);
}

template<typename T>
T* Entity::CreateEntity(SpriteData* _sprite)
{
	return GetScene()->CreateEntity<T>(_sprite);
}


template<typename T>
inline Entity* Entity::CreateClonedEntity()
{
	AssetManager& am = AssetManager::getInstance();

	T* newEntity = nullptr;

	if (hasSprite)
	{
		int w = m_sprite->data->spritesheet ? m_sprite->data->frameSizeW : m_sprite->data->sizeW;
		int h = m_sprite->data->spritesheet ? m_sprite->data->frameSizeH : m_sprite->data->sizeH;

		newEntity = CreateEntity<T>(am.CreateSprite(m_sprite->textureID, 0, 0, w, h));
		newEntity->SetSpriteScale(m_sprite->sprite->getScale().x, m_sprite->sprite->getScale().y);
		newEntity->SetSpriteRotation(m_sprite->sprite->getRotation());
	}
	else
	{
		newEntity = CreateEntity<T>(mShape.getSize().x, mShape.getSize().y, mShape.getFillColor());
	}

	newEntity->SetTag(mTag);
	newEntity->SetMoveAble(m_isMoveable);
	newEntity->SetRigidBody(mRigidBody);

	return newEntity;
}
