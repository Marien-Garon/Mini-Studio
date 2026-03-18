#include "Scene.h"

#include "GameManager.h"

int Scene::GetWindowWidth() const
{
	return GameManager::Get()->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return GameManager::Get()->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return GameManager::Get()->mDeltaTime;
}

void Scene::DrawSprite(sf::Sprite* _sprite) const
{
	GameManager::Get()->DrawSprite(_sprite);
}
