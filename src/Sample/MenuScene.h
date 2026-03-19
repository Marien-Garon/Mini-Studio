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
	Button* m_buttonPlay;
	Entity* m_menuScreen;
	Entity* m_encadre;
	Entity* m_menuFond;
	Button* m_arrowLeft;
	Button* m_arrowRight;
	Button* m_buttonExit;
	std::vector<std::string> menuOptions = { "Play", "Settings", "Quit" };
	int currentOption = 0;

private:

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};


