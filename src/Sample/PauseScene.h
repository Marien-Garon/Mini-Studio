#pragma once
#include "Scene.h"

class PauseScene : public Scene
{
private:

	Entity* m_pauseMenu;
	Entity* m_buttonContinue;
	Entity* m_buttonRestart;
	Entity* m_buttonSave;
	Entity* m_buttonSettings;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

};


