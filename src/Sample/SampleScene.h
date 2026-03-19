#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Button.h"
#include "Companion.h"

class Enemy;
class Camera;
class Platform;
class Button;

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
	Button* m_buttonContinue;
	Button* m_buttonRestart;
	Button* m_buttonSave;
	Button* m_buttonSettings;
	Button* m_buttonExit;

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


