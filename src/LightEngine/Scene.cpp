#include "Scene.h"

#include "GameManager.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}

void Scene::DrawSprite(sf::Sprite* _sprite) const
{
	mpGameManager->DrawSprite(_sprite);
}