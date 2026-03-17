#pragma once
#include "Scene.h"
#include "Enemy.h"

class Platform;

class PhysicalEntity;
class Enemy;
class Camera;

class SampleScene : public Scene
{
	Enemy* pEntity1;
	Enemy* pEntity2;
	
	std::vector<Platform*> m_Platforms;
	
	
	//std::vector<Entity*> 


	//Enemy* pEntitySelected;
	Camera* mCamera;
	

	PhysicalEntity* pEntitySelected;
private:
	void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
	
	void OnDestroy() override {};
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


