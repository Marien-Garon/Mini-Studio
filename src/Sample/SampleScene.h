#pragma once
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

class PhysicalEntity;
class Enemy;
class Camera;

class SampleScene : public Scene
{
	Player* test_Entity;
	/*..Enemy* pEntity1;
	..Enemy* pEntity2;*/

	//Enemy* pEntitySelected;
	Camera* mCamera;
	

	Entity* pEntitySelected;
private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


