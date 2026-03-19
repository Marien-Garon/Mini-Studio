#include "SampleScene.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "PauseScene.h"
#include "LevelEditor.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0});

	pInstance->CreateWindow(1280, 720, "HyperBlast: The Key-Star!", 60, {0,0,0}, false);
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