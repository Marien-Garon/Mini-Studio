#pragma once
#include "Scene.h"

class Button;

class PauseScene : public Scene
{
private:

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

};


