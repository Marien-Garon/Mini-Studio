#pragma once

#include "Scene.h"

class Companion;

class SampleScene : public Scene
{
	Companion* pEntity1;
	Companion* pEntity2;

	Companion* pEntitySelected;

private:
	void TrySetSelectedEntity(Companion* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


