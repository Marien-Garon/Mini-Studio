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


class SampleScene : public Scene
{
private:
    

	float test_BPMDeLaMusique = 135;
	float test_tempsEntreLesAttaque = 60 / test_BPMDeLaMusique; //temps entre chaque appuye en seconde
	float test_timerAttaque = 0;
	float m_pityFrames = 10.f;

	Player* m_player;
	Companion* m_robot;

	std::vector<Platform*> m_Platforms;
	std::vector<Entity*> m_UI;

public:

	void OnDestroy() override {};
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

private:

	std::vector<Hook*> m_hooks;
	Parallaxe* m_parallaxe;
	Mob1* test;


public:
	std::vector<Hook*> GetHooks() { return m_hooks; };
	Player* GetPlayer() { return m_player; }

	bool IsAttackTimingOkay();
	void IncreaseTimer();
	Camera* GetCamera() const;
};
