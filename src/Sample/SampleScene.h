#pragma once

#include "Scene.h"

class Player;
class Hook;

class SampleScene : public Scene
{
	Player* m_player;

	std::vector<Hook*> m_hooks;

private:

public:
	std::vector<Hook*> GetHooks();
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


