#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "PauseScene.h"
#include "DeathScene.h"


int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "HyperBlast: The Key-Star!", 60, {0,0,0}, false);

	SceneManager& sm = SceneManager::getInstance();

	MenuScene menuScene;
	SampleScene sampleScene;
	PauseScene pauseScene;
	DeathScene deathScene;


	sm.AddScene("START", &menuScene);
	sm.AddScene("LEVEL", &sampleScene);
	sm.AddScene("PAUSE", &pauseScene);
	sm.AddScene("DEATH", &deathScene);

	sm.SetStartScene("START");

	pInstance->SetScene(sm.GetCurrentScene());
	pInstance->Run();

	//bool LaunchLevelEditor = false;

	//if (LaunchLevelEditor)
	//	pInstance->LaunchScene<LevelEditor>();
	//else
	//	pInstance->LaunchScene<SampleScene>();
	return 0;
}