#include "DeathScene.h"

#include "Entity.h"
#include "Scene.h"

#include "GameManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "AssetManager.h"

#include "Camera.h"


void DeathScene::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();
	AM.StopMusic();


	m_deathScreen = CreateEntity<Entity>(AM.CreateSprite("Menu_lose",0,0, 1116, 1070));
	m_deathScreen->SetScale(0.70,0.70);
	m_deathScreen->SetPosition(0, 0, 1.f, 1.f);

	mCamera = CreateEntity<Camera>(0, 0, sf::Color::Black);
	mCamera->SetupCamera(0, m_deathScreen);

	GameManager::Get()->RefreshCamera(mCamera);
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
