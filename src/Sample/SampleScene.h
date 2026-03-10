#pragma once
#include "Scene.h"

class Enemy;

class SampleScene : public Scene
{
    Enemy* pEntitySelected;
    std::vector<Enemy*> m_enemy;

private:
    void TrySetSelectedEntity(Enemy* pEntity, int x, int y);

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

private:
    Enemy* SpawnEnemy(int x, int y);
};
