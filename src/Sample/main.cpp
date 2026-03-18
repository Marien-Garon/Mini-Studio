#include "SampleScene.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "MenuScene.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0});

	SceneManager& sm = SceneManager::getInstance();

	sm.AddScene("START", new MenuScene);
	sm.AddScene("LEVEL", new SampleScene);

	sm.SetStartScene("START");

	pInstance->SetScene(sm.GetCurrentScene());
	pInstance->Run();

	return 0;
}