#pragma once
#include "SceneManager.h"
#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	//_ASSERT(mpScene == nullptr);
	_ASSERT(SceneManager::getInstance().GetCurrentScene() == nullptr);
	
	T* newScene = new T();
	mpScene = newScene;
	mpScene->OnInitialize();

	Run();
}
