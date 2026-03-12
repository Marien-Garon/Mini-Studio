#pragma once

#include "Scene.h"
#include "DummyEntity.h"
#include "Enemy.h"

class PhysicalEntity;

class SampleScene : public Scene
{
	int test_NombreAppuyeAttaque = 0;
	Enemy* pEntity2;

	Enemy* pEntitySelected;

	
private:
	void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


