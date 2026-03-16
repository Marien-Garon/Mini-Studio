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

	m_buttonContinue->CreateEntity<Entity>(100, 50, sf::Color::Red);
	m_buttonContinue->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
}

void PauseScene::OnEvent(const sf::Event& event)
{

}


void PauseScene::OnUpdate()
{
  
}
