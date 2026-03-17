#pragma once
#include "Scene.h"
#include <unordered_map>


class SceneManager
{
private:

	std::unordered_map<std::string, Scene*> m_sceneList;

	Scene* currentScene;

public:

	~SceneManager();


	Scene* GetCurrentScene() { return currentScene; };

	void SetScene(const std::string& _id);

};
