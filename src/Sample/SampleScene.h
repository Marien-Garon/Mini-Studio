#pragma once
#include "PhysicalEntity.h"
#include "Scene.h"

class Player;

class SampleScene : public Scene
{
	Player* player;

	Player* pEntitySelected;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


