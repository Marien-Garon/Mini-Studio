#pragma once
#include "Scene.h"
#include "TileBlock.h"

class LevelEditor : public Scene
{
private:

	std::vector<TileBlock*> m_tileList;
	std::vector<Entity*> m_entityToPlace;

	std::vector<TileBlock*> m_posedBlock;


	Entity* pEntitySelected = nullptr;

public:

	void SaveLevel();
	void EraseCurrentLevel();
	bool CanPoseTile(float _x, float _y);
	
	float GetScale(float size, float target);
	//float truc2(float size, float target); //Le premier qui delete ça aura affaire a moi

	void InitTileBlock();

	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

	void CreateEntityCopy(Entity* _entity, int _x, int _y);

	virtual void OnDestroy() override;
	virtual void OnInitialize() override;
	virtual void OnEvent(const sf::Event& event) override;
	virtual void OnUpdate() override;
};