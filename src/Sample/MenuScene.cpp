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

	m_encadre = CreateEntity<Entity>(AM.LoadSprite("encadre lumineux"), sf::Color::Green);
	m_encadre->SetSpriteScale(0.67, 0.67);

	m_buttonPlay = CreateEntity<Button>(AM.LoadSprite("play"), sf::Color::Red);
    sf::Vector2f buttonPos((GetWindowWidth() / 2) + 80.f, (GetWindowHeight() / 2) + 25.f);
	m_buttonPlay->SetSpriteScale(0.67, 0.67);
	m_buttonPlay->SetPosition(buttonPos.x, buttonPos.y);
	

	m_buttonPlay->SetFunction([]() {

	   SceneManager& SM = SceneManager::getInstance();
	   SM.ChangeScene("LEVEL");
	});

	
	sf::Vector2f playButtonPos = m_buttonPlay->GetPosition(0.f, 0.5f);

	m_arrowLeft = CreateEntity<Button>(AM.LoadSprite("fleche gauche"), sf::Color::Transparent);
	m_arrowLeft->SetSpriteScale(0.67, 0.67);
	m_arrowLeft->SetPosition(15.f, 22.f);

	playButtonPos = m_buttonPlay->GetPosition(1.f, 0.5f);
	m_arrowRight = CreateEntity<Button>(AM.LoadSprite("fleche droit"), sf::Color::Transparent);
	m_arrowRight->SetSpriteScale(0.67, 0.67);
	m_arrowRight->SetPosition(130.f, 22.f);

	m_buttonExit = CreateEntity<Button>(AM.LoadSprite("bouton off"), sf::Color::Transparent);
	m_buttonExit->SetSpriteScale(0.67, 0.67);
	m_buttonExit->SetPosition(895.f, 652.f);

	m_buttonExit->SetFunction([]() {
		GameManager* GM = GameManager::Get();
		GM->GetWindow()->close();
		});
  
}

void MenuScene::OnEvent(const sf::Event& event)
{
	m_buttonPlay->UpdateEvent(event);
}


void MenuScene::OnUpdate()
{
	float buttonWidth = 338;
	float buttonHeight = 138;

	AssetManager& AM = AssetManager::getInstance();

	InputManager& IM = InputManager::Get();
	sf::Vector2i mousePos = IM.GetMousePos();

	if (m_buttonPlay->IsInside(mousePos.x, mousePos.y))
	{
		m_encadre->SetPosition(m_buttonPlay->GetPosition().x + 78.f, m_buttonPlay->GetPosition().y + 50.f);
	}
	else
	{
		m_encadre->SetPosition(-1000, -1000);
	}

	if (m_arrowLeft->IsInside(mousePos.x, mousePos.y))
	{
		m_arrowLeft->SetSprite(AM.LoadSprite("fleche gauche allume"));

	}else {
		m_arrowLeft->SetSprite(AM.LoadSprite("fleche gauche"));
	}

	if (m_arrowRight->IsInside(mousePos.x, mousePos.y))
	{
		m_arrowRight->SetSprite(AM.LoadSprite("fleche droit allume"));
	}
	else
	{
		m_arrowRight->SetSprite(AM.LoadSprite("fleche droit"));
	}

	if (m_buttonExit->IsInside(mousePos.x, mousePos.y))
	{
		m_buttonExit->SetSprite(AM.LoadSprite("bouton off allume"));
	}
	else
	{
		m_buttonExit->SetSprite(AM.LoadSprite("bouton off"));
	}

	m_arrowLeft->SetSpriteScale(0.67, 0.67);
	m_arrowRight->SetSpriteScale(0.67, 0.67);
	m_buttonExit->SetSpriteScale(0.67, 0.67);

	m_buttonExit->SetPosition(895.f, 652.f);
	m_arrowRight->SetPosition(845.f, 360.f);
	m_arrowLeft->SetPosition(450.f, 360.f);
}
