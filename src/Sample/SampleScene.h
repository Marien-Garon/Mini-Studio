#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Companion.h"

class Enemy;
class Camera;
class Platform;

class SampleScene : public Scene
{
	float test_BPMDeLaMusique = 135;
	float test_tempsEntreLesAttaque = 60 / test_BPMDeLaMusique; //temps entre chaque appuye en seconde
	float test_timerAttaque = 0;
	float m_pityFrames = 10.f;

	Player* m_player;
	Companion* m_robot;
	Camera* mCamera;
	std::vector<Platform*> m_Platforms;
	std::vector<Entity*> m_UI;
	
	std::vector<Hook*> m_hooks;
private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);
	
public :
	bool mIsPaused = false;

private :
	Entity* m_pauseMenu;
	Entity* m_buttonContinue;
	Entity* m_buttonRestart;
	Entity* m_buttonSave;
	Entity* m_buttonSettings;
	Entity* m_buttonExit;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	std::vector<Hook*> GetHooks() { return m_hooks; };
	Player* GetPlayer() { return m_player; }
	void SetPause();
	void UnPause();
	bool IsAttackTimingOkay();
	void IncreaseTimer();
};


