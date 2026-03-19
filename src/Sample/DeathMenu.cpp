#include "DeathMenu.h"

#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Companion.h"
#include "Button.h"
#include "SceneManager.h"
#include "AssetManager.h"

void DeathMenu::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	m_deathScreen = CreateEntity<Entity>(AM.LoadSprite("menu"), sf::Color::Red);
	m_deathScreen->SetSpriteScale(0.333, 0.333);

	m_quitButton = CreateEntity<Button>(110, 50, sf::Color::Transparent);
	m_replayButton = CreateEntity<Button>(110, 50, sf::Color::Transparent);

	m_replayButton->SetFunction([]() {

		SceneManager& SM = SceneManager::getInstance();
		SM.ChangeScene("LEVEL");
		});

	m_quitButton->SetFunction([]() {

		SceneManager& SM = SceneManager::getInstance();
		exit(1);
		});

}
