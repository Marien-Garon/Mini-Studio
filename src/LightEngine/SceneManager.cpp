#include "SceneManager.h"

Scene* SceneManager::GetCurrentScene()
{
}

void SceneManager::ChangeScene(const std::string& _num)
{
    m_nextScene = _num;
    m_changeScene = true;
}

void SceneManager::AddScene(const std::string& _num, Scene* _scene)
{
}

void SceneManager::SetStartScene(const std::string& _num)
{
}
