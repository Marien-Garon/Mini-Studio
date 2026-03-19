#include "SampleScene.h"
#include "GameManager.h"
#include "LevelEditor.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	bool LaunchLevelEditor = false;

	pInstance->CreateWindow(1280, 720, "HyperBlast: The Key-Star!", 60, {0,0,0}, false);

	if (LaunchLevelEditor)
		pInstance->LaunchScene<LevelEditor>();
	else
		pInstance->LaunchScene<SampleScene>();

	return 0;
}