#include "MenuScene.h"
#include <iostream>
#include "Enemy.h"
#include "Entity.h"

#include "Utils.h"
#include "Debug.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Button.h"
#include "SceneManager.h"


void MenuScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	m_menuFond = CreateEntity<Entity>(AM.CreateSprite("fond-menu"));
	m_menuFond->SetScale(0.67, 0.67);

	m_menuScreen = CreateEntity<Entity>(AM.CreateSprite("menu"));
	sf::Vector2f pos = m_menuScreen->GetPosition();
	m_menuScreen->SetScale(0.67, 0.67);
	m_menuScreen->SetPosition(pos.x + 105.0f, pos.y );

	m_encadre = CreateEntity<Entity>(AM.CreateSprite("encadre lumineux"));
	m_encadre->SetScale(0.67, 0.67);

	m_buttonPlay = CreateEntity<Button>(AM.CreateSprite("play"));
    sf::Vector2f buttonPos((GetWindowWidth() / 2) + 80.f, (GetWindowHeight() / 2) + 25.f);
	m_buttonPlay->SetScale(0.67, 0.67);
	m_buttonPlay->SetPosition(buttonPos.x, buttonPos.y);
	

	m_buttonPlay->SetFunction([]() {

	   SceneManager& SM = SceneManager::getInstance();
	   SM.ChangeScene("LEVEL");
	   });

	
	sf::Vector2f playButtonPos = m_buttonPlay->GetPosition(0.f, 0.5f);

	/*m_arrowLeft = CreateEntity<Button>(AM.CreateSprite("fleche gauche"));
	m_arrowLeft->SetScale(0.67, 0.67);
	m_arrowLeft->SetPosition(15.f, 22.f);

	playButtonPos = m_buttonPlay->GetPosition(1.f, 0.5f);
	m_arrowRight = CreateEntity<Button>(AM.CreateSprite("fleche droit"));
	m_arrowRight->SetScale(0.67, 0.67);
	m_arrowRight->SetPosition(130.f, 22.f);

	m_buttonExit = CreateEntity<Button>(AM.CreateSprite("bouton off"));
	m_buttonExit->SetScale(0.67, 0.67);
	m_buttonExit->SetPosition(895.f, 652.f);*/

	//m_buttonExit->SetFunction([]() {
	//	GameManager* GM = GameManager::Get();
	//	GM->GetWindow()->close();
	//	});
 // 
}

void MenuScene::OnEvent(const sf::Event& event)
{
	//m_buttonPlay->UpdateEvent(event);
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

	/*if (m_arrowLeft->IsInside(mousePos.x, mousePos.y))
	{
		m_arrowLeft->SetSprite(AM.CreateSprite("fleche gauche allume"));

	}else {
		m_arrowLeft->SetSprite(AM.CreateSprite("fleche gauche"));
	}

	if (m_arrowRight->IsInside(mousePos.x, mousePos.y))
	{
		m_arrowRight->SetSprite(AM.CreateSprite("fleche droit allume"));
	}
	else
	{
		m_arrowRight->SetSprite(AM.CreateSprite("fleche droit"));
	}

	if (m_buttonExit->IsInside(mousePos.x, mousePos.y))
	{
		m_buttonExit->SetSprite(AM.CreateSprite("bouton off allume"));
	}
	else
	{
		m_buttonExit->SetSprite(AM.CreateSprite("bouton off"));
	}*/

	//m_arrowLeft->SetScale(0.67, 0.67);
	//m_arrowRight->SetScale(0.67, 0.67);
	//m_buttonExit->SetScale(0.67, 0.67);

	//m_buttonExit->SetPosition(895.f, 652.f);
	//m_arrowRight->SetPosition(845.f, 360.f);
	//m_arrowLeft->SetPosition(450.f, 360.f);
}
