#pragma once
#include "PhysicalEntity.h"
#include "Scene.h"
#include "DummyEntity.h"
#include "Enemy.h"

class PhysicalEntity;
class Player;
class Companion;

class SampleScene : public Scene
{
private: 

	float test_BPMDeLaMusique = 135;
	float test_tempsEntreLesAttaque = 60 / test_BPMDeLaMusique; //temps entre chaque appuye en seconde
	float test_timerAttaque = 0;

	Player* m_player;
	Companion* m_robot;
	Player* pEntitySelected;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	
	Player* GetPlayer() { return m_player;  }
	bool IsAttackTimingOkay();
	void IncreaseTimer();
};


