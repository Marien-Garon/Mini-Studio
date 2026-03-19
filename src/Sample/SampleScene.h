#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

#include"Platform.h"

#include "Companion.h"
#include "Parallaxe.h"


class Enemy;
class Platform;
class Camera;
class Platform;
class Mob1;
class PauseScene;


class SampleScene : public Scene
{
private:
    

	float test_BPMDeLaMusique = 135;
	float test_tempsEntreLesAttaque = 60 / test_BPMDeLaMusique; //temps entre chaque appuye en seconde
	float test_timerAttaque = 0;
	float m_pityFrames = 10.f;
	bool mIsPaused = false;


	Player* m_player;
	Companion* m_robot;

	std::vector<Platform*> m_Platforms;
	std::vector<Entity*> m_UI;

	sf::Vector2f m_playerStartPos = { 0.f,0.f };
	PauseScene* m_pauseMenu;

public:

	void AddHook(Hook* hook) { m_hooks.push_back(hook); };
	void SetPlayerPos(sf::Vector2f pos) { m_playerStartPos = pos; };


	void OnDestroy() override {};
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

	bool mIsPaused = false;

private:

	std::vector<Hook*> m_hooks;
	Parallaxe* m_parallaxe;
	//Mob1* test;


public:
	std::vector<Hook*> GetHooks() { return m_hooks; };
	Player* GetPlayer() { return m_player; }
	void SetPaused(bool paused) { mIsPaused = paused; }
	bool IsAttackTimingOkay();
	void IncreaseTimer();
	Camera* GetCamera() const;
};
