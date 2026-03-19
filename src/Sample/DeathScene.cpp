#include "DeathScene.h"

#include "Entity.h"
#include "Scene.h"


#include "Button.h"
#include "SceneManager.h"
#include "AssetManager.h"

void DeathScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	AM.StopMusic();

	m_deathScreen = CreateEntity<Entity>(AM.LoadSprite("Balladeur"));
	//m_deathScreen->SetSpriteScale(0.333, 0.333);
	m_deathScreen->SetPosition(GetWindowWidth(), GetWindowHeight(), 1.f, 1.f);

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
