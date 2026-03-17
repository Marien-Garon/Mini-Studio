#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Companion.h"

class Enemy;
class Camera;

class MenuScene : public Scene
{
	Entity* m_buttonPlay;
	Entity* m_menuScreen;
	Entity* m_arrowLeft;
	Entity* m_arrowRight;
	Entity* m_buttonExit;

private:

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};


