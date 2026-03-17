#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	bool LaunchLevelEditor = false;

	pInstance->CreateWindow(1920, 1080, "Sample", 60, {0,0,0}, true);

	if (LaunchLevelEditor)
		pInstance->LaunchScene<LevelEditor>();
	else
		pInstance->LaunchScene<SampleScene>();


	return 0;
}