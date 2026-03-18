#include "SceneManager.h"

Scene* SceneManager::GetCurrentScene()
{
    return m_scene[m_currentScene];
}

void SceneManager::ChangeScene(const std::string& _num)
{
    m_nextScene = _num;
    m_changeScene = true;
}

void SceneManager::AddScene(const std::string& _num, Scene* _scene)
{
    m_scene[_num] = _scene;
}

void SceneManager::SetStartScene(const std::string& _num)
{ 
    m_currentScene = _num;
    m_nextScene = _num;
}

bool SceneManager::Update()
{
    if (m_changeScene)
    {
        m_currentScene = m_nextScene;
        m_changeScene = false;
        return true;
    }
    return false;
}