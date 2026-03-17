#include "SceneManager.h"

SceneManager::~SceneManager()
{
	for (auto& pair : m_sceneList)
		delete pair.second;

	m_sceneList.clear();
}

void SceneManager::SetScene(const std::string& _id)
{
	if (!m_sceneList.contains(_id)) return;
	

	currentScene = m_sceneList[_id];
}
