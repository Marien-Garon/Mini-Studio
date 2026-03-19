#include "MenuScene.h"
#include <iostream>
#include "DummyEntity.h"
#include "Enemy.h"
#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Camera.h"
#include "Button.h"
#include "SceneManager.h"


void MenuScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	m_menuFond = CreateEntity<Entity>(AM.LoadSprite("fond-menu"), sf::Color::Red);
	m_menuFond->SetSpriteScale(0.67, 0.67);

	m_menuScreen = CreateEntity<Entity>(AM.LoadSprite("menu"), sf::Color::Red);
	sf::Vector2f pos = m_menuScreen->GetPosition();
	m_menuScreen->SetSpriteScale(0.67, 0.67);
	m_menuScreen->SetPosition(pos.x + 105.0f, pos.y );

	m_encadre = CreateEntity<Entity>(350, 150, sf::Color::Green);

	m_buttonPlay = CreateEntity<Button>(338, 138, sf::Color::Red);
    sf::Vector2f buttonPos((GetWindowWidth() / 2) - 1.5f, (GetWindowHeight() / 2) - 9);
    m_buttonPlay->SetPosition(buttonPos.x, buttonPos.y);

	m_buttonPlay->SetFunction([]() {

	   SceneManager& SM = SceneManager::getInstance();
	   SM.ChangeScene("LEVEL");
	});

	

	m_arrowLeft = CreateEntity<Button>(30, 40, sf::Color::Transparent);
	m_arrowLeft->SetPosition((GetWindowWidth() / 2) - 110, (GetWindowHeight() / 2));

	m_arrowRight = CreateEntity<Button>(30, 40, sf::Color::Transparent);
	m_arrowRight->SetPosition((GetWindowWidth() / 2) - 60, (GetWindowHeight() / 2));

	m_buttonExit = CreateEntity<Button>(50, 50, sf::Color::Transparent);
	m_buttonExit->SetPosition((GetWindowWidth() / 2) - 106, (GetWindowHeight() / 2) + 63);
  
}

void MenuScene::OnEvent(const sf::Event& event)
{
	m_buttonPlay->UpdateEvent(event);
}


void MenuScene::OnUpdate()
{
	float buttonWidth = 338;
	float buttonHeight = 138;

	sf::Vector2i mousePos = sf::Mouse::getPosition();

	InputManager& IM = InputManager::Get();

	if (m_buttonPlay->IsInside(IM.GetMousePos().x, IM.GetMousePos().y))
	{
		m_encadre->SetPosition(m_buttonPlay->GetPosition().x, m_buttonPlay->GetPosition().y);
	}
	else
	{
		m_encadre->SetPosition(-1000, -1000);
	}
}
