#pragma once
#include "Scene.h"
#include "Enemy.h"
#include"Mob1.h"

class Enemy;
class Camera;

class SampleScene : public Scene
{
    Enemy* pEntitySelected;
    
    std::vector<Enemy*> m_enemy;
	std::vector<Platform*> m_Platforms;
	
	
private:
    void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

private:
    Enemy* SpawnEnemy(int x, int y);
};
