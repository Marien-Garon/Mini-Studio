#pragma once
#include "PhysicalEntity.h"
#include "Scene.h"

class Player;
class Companion;

class SampleScene : public Scene
{
	PhysicalEntity* kaka;
	Player* player;
	Companion* robot;
	Player* pEntitySelected;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


