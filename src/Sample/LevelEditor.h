#pragma once
#include "Scene.h"
#include "TileBlock.h"
#include "BreakablePlatform.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Button;



class LevelEditor : public Scene
{
private:

	std::vector<std::vector<Entity*>> m_SelectionPage;
	std::vector<Entity*> m_posedBlock;

	std::vector <std::vector<Entity*>> m_gridList;

	std::vector<Button*> btnList;

	Entity* pEntitySelected = nullptr;

	int currentSelectionIndex = 0;
	int currentGrid = 0;
	bool drawGrid = true;

public:

	static std::vector<Entity*> LoadLevel(Scene* scene, std::string _id);

	void SaveLevel();
	void EraseCurrentLevel();
	bool CanPoseTile(float _x, float _y);

	
	void ReplaceGrid();

	void ReplaceTile();
	void RemoveTile(int _index);
	
	void IndexMove(int _movement);

	std::vector<Entity*> GetPresentTile(float _x, float _y);


	float GetScale(float size, float target);
	//float truc2(float size, float target); //Le premier qui delete ça aura affaire a moi

	void InitEntity();
	void InitTileBlock();

	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

	void CreateEntityCopy(Entity* _entity, int _x, int _y);

	void DrawGrid();

	void OnDestroy() override;
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};