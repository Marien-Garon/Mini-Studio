#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"
#include "Debug.h"

#include <SFML/Graphics/Sprite.hpp>

template<typename T>
T* Scene::CreateEntity(float width, float height, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->Initialize(width, height, color);
	
	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}


template<typename T>
T* Scene::CreateEntity(SpriteData* _sprite)
{
	if (_sprite->sprite == nullptr)
	{
		Debug::DebugMessage(Debug::Severity::CRITICAL, "Create Entity", "Received a nullptr Sprite ABORT MISSION ABPORT MISSION MAYDAY MAYDA EZ-5 AAAAAAAAH");
		return nullptr;
	}


	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();


	Entity* entity = newEntity;

	entity->SetSprite(_sprite);
	entity->Initialize(_sprite->sprite->getTextureRect().width, _sprite->sprite->getTextureRect().height, sf::Color::Transparent);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}