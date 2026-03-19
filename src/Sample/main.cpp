#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"
//#include "MenuScene.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	bool LaunchLevelEditor = false;

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0}, true);

	MenuScene menuScene;
	SampleScene sampleScene;
	PauseScene pauseScene;
	DeathMenu deathMenu;

	sm.AddScene("START", &menuScene);
	sm.AddScene("LEVEL", &sampleScene);
	sm.AddScene("PAUSE", &pauseScene);
	sm.AddScene("DEATH", &deathMenu);

	sm.SetStartScene("START");


	return 0;
}