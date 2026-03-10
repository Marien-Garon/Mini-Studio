#pragma once

#include "Scene.h"



class Enemy;

class SampleScene : public Scene
{
	Enemy* pEntity1;

	Enemy* pEntitySelected;

private:
	void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


