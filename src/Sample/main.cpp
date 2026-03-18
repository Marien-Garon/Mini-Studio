#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	bool LaunchLevelEditor = true;

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0}, false);

	if (LaunchLevelEditor)
		pInstance->LaunchScene<LevelEditor>();
	else
		pInstance->LaunchScene<SampleScene>();


	return 0;
}