#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"

#include <iostream>

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
T* Scene::CreateEntity(sf::Sprite* _sprite, const sf::Color& color)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();


	Entity* entity = newEntity;

	if (_sprite == nullptr) std::cout << "ALERTE " << std::endl;

	entity->Initialize(_sprite->getTextureRect().width, _sprite->getTextureRect().height, color);
	entity->SetSprite(_sprite);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}