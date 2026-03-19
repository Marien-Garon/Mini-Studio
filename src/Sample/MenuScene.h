#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "Companion.h"

class Enemy;
class Camera;
class Button;

class MenuScene : public Scene
{
	Entity* m_menuFond;
	Entity* m_encadre;

	Button* m_buttonPlay;
	Entity* m_menuScreen;
	Button* m_arrowLeft;
	Button* m_arrowRight;
	Button* m_buttonExit;

private:

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};


