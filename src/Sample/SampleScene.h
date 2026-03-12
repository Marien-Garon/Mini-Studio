#pragma once
#include "Scene.h"

class PhysicalEntity;
class Enemy;
class Camera;

class SampleScene : public Scene
{
	Enemy* pEntity1;
	Enemy* pEntity2;

	Camera* mCamera;

	PhysicalEntity* pEntitySelected;
private:
	void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


