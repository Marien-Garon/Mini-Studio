#include "SampleScene.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "PauseScene.h"
#include "DeathMenu.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0});

	SceneManager& sm = SceneManager::getInstance();

	MenuScene menuScene;
	SampleScene sampleScene;
	PauseScene pauseScene;
	DeathMenu deathMenu;

	sm.AddScene("START", &menuScene);
	sm.AddScene("LEVEL", &sampleScene);
	sm.AddScene("PAUSE", &pauseScene);
	sm.AddScene("DEATH", &pauseScene);

	sm.SetStartScene("START");

	pInstance->SetScene(sm.GetCurrentScene());
	pInstance->Run();

	return 0;
}