#include "PauseScene.h"
#include <iostream>
#include "DummyEntity.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Camera.h"


void PauseScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	m_pauseMenu = CreateEntity<Entity>(AM.LoadSprite("pause"), sf::Color::Red);
	m_pauseMenu->SetSpriteScale(0.333, 0.333);

	m_buttonContinue = CreateEntity<Entity>(350, 65, sf::Color::Red);
	m_buttonContinue->SetPosition((GetWindowWidth() / 2) - 20, (GetWindowHeight() / 2) - 59);

	m_buttonRestart = CreateEntity<Entity>(350, 65, sf::Color::Red);
	m_buttonRestart->SetPosition((GetWindowWidth() / 2) - 20, (GetWindowHeight() / 2) + 36);

	m_buttonSave = CreateEntity<Entity>(350, 65, sf::Color::Red);
	m_buttonSave->SetPosition((GetWindowWidth() / 2) - 20, (GetWindowHeight() / 2) + 130);

	m_buttonSettings = CreateEntity<Entity>(350, 65, sf::Color::Red);
	m_buttonSettings->SetPosition((GetWindowWidth() / 2) - 20, (GetWindowHeight() / 2) + 220);

	m_buttonExit = CreateEntity<Entity>(100, 65, sf::Color::Red);
	m_buttonExit->SetPosition((GetWindowWidth() / 2) + 410, (GetWindowHeight() / 2) + 300);
}

void PauseScene::OnEvent(const sf::Event& event)
{

}


void PauseScene::OnUpdate()
{
  
}
