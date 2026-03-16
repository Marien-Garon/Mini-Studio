#pragma once
#include "Scene.h"
#include "TileBlock.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Button;



class LevelEditor : public Scene
{
private:

	std::vector<std::vector<TileBlock*>> m_page;

	std::vector<TileBlock*> m_tileList;
	std::vector<Entity*> m_entityToPlace;

	std::vector<TileBlock*> m_posedBlock;

	std::vector<Button*> btnList;

	Entity* pEntitySelected = nullptr;

	int currentIndex = 0;

public:

	void SaveLevel();
	void EraseCurrentLevel();
	bool CanPoseTile(float _x, float _y);

	void ReplaceTile();
	void RemoveTile(int _index);
	
	void IndexMove(int _movement);

	TileBlock* GetPresentTile(float _x, float _y);


	float GetScale(float size, float target);
	//float truc2(float size, float target); //Le premier qui delete ça aura affaire a moi

	void InitTileBlock();

	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

	void CreateEntityCopy(Entity* _entity, int _x, int _y);

	void DrawGrid();

	void OnDestroy() override;
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};