#include "SampleScene.h"
#include "GameManager.h"
#include "PauseScene.h"

int main()
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Sample", 60, {0,0,0});

	pInstance->LaunchScene<PauseScene>();

	return 0;
}