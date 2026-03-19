#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "PauseScene.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	bool LaunchLevelEditor = false;

	pInstance->CreateWindow(1280, 720, "HyperBlast: The Key-Star!", 60, {0,0,0}, false);

	if (LaunchLevelEditor)
		pInstance->LaunchScene<LevelEditor>();
	else
		pInstance->LaunchScene<SampleScene>();
	SceneManager& sm = SceneManager::getInstance();

	MenuScene menuScene;
	SampleScene sampleScene;
	PauseScene pauseScene;

	sm.AddScene("START", &menuScene);
	sm.AddScene("LEVEL", &sampleScene);
	sm.AddScene("PAUSE", &pauseScene);

	sm.SetStartScene("START");

	pInstance->SetScene(sm.GetCurrentScene());
	pInstance->Run();

	return 0;
}