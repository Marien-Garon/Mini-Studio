#pragma once

#include "Scene.h"

#include "Enemy.h"

class Platform;

class PhysicalEntity;

class SampleScene : public Scene
{
	Enemy* pEntity1;

	Enemy* pEntity2;

	Enemy* pEntitySelected;

	std::vector<Platform*> m_Platforms;
	
	
private:
	void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


