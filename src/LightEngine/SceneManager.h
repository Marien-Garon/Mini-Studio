#pragma once
#include "Scene.h"
#include <map>

class SceneManager
{
public:

	Scene* GetCurrentScene();
	bool Update();
	void ChangeScene(const std::string& _num);
	void AddScene(const std::string& _num, Scene* _scene);
	void SetStartScene(const std::string& _num);

	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}

private:

	std::map<std::string, Scene*> m_scene;
	std::string m_currentScene;
	std::string m_nextScene;
	bool m_changeScene;
};

