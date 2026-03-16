#include "MenuScene.h"
#include <iostream>
#include "DummyEntity.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Camera.h"


void MenuScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	m_menuScreen = CreateEntity<Entity>(AM.LoadSprite("menu"), sf::Color::Red);
	m_menuScreen->SetSpriteScale(0.333, 0.333);

   m_buttonPlay = CreateEntity<Entity>(110, 50, sf::Color::Red);
   m_buttonPlay->SetPosition((GetWindowWidth() / 2) - 12 ,(GetWindowHeight() / 2) - 79) ;

   m_arrowLeft = CreateEntity<Entity>(30, 40, sf::Color::Red);
   m_arrowLeft->SetPosition((GetWindowWidth() / 2) - 110, (GetWindowHeight() / 2));
   
   m_arrowRight = CreateEntity<Entity>(30, 40, sf::Color::Red);
   m_arrowRight->SetPosition((GetWindowWidth() / 2) - 60, (GetWindowHeight() / 2));

   m_buttonExit = CreateEntity<Entity>(50, 50, sf::Color::Red);
   m_buttonExit->SetPosition((GetWindowWidth() / 2) - 100, (GetWindowHeight() / 2) + 64);

}

void MenuScene::OnEvent(const sf::Event& event)
{

}


void MenuScene::OnUpdate()
{
  
}
