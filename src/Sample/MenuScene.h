#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Companion.h"

class Enemy;
class Camera;

class MenuScene : public Scene
{
	float test_BPMDeLaMusique = 135;
	float test_tempsEntreLesAttaque = 60 / test_BPMDeLaMusique; //temps entre chaque appuye en seconde
	float test_timerAttaque = 0;

	Player* m_player;
	Companion* m_robot;
	Camera* mCamera;

	Entity* m_buttonPlay;
	Entity* m_menuScreen;
	Entity* m_arrowLeft;
	Entity* m_arrowRight;
	Entity* m_buttonExit;

	Entity* pEntitySelected;

private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};


