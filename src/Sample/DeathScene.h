#pragma once
#include "Scene.h"


class Button;

class DeathScene :
	public Scene
{
private:
	Entity* m_deathScreen;

	Button* m_replayButton;
	Button* m_quitButton;


public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override {};
	void OnUpdate() override {};

};

