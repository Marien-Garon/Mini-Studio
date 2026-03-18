#include "LevelEditor.h"
#include "AssetManager.h"
#include "Debug.h"
#include "Button.h"
#include <iostream>
#include "InputManager.h"
#include "Hook.h"

#define TILE_SIZE 64.f

std::vector<Entity*> LevelEditor::LoadLevel(Scene* scene, std::string _id)
{
	std::filesystem::path levelPath = "../../../level/" + _id;
	if (levelPath.extension() != ".json") levelPath += ".json";

	if (!std::filesystem::exists(levelPath))
	{
		Debug::DebugMessage(Debug::Severity::WARN, "Load Level", "Level : " + _id + " doesn't exist");
		return {};
	}

	std::ifstream jsonFile(levelPath);

	if (!jsonFile.is_open())
	{
		Debug::DebugMessage(Debug::Severity::WARN, "Load JSON", "Can't open JSON file : " + levelPath.string());
		return {};
	}

	json jsonData;
	jsonFile >> jsonData;
	jsonFile.close();

	std::vector<Entity*> m_entity;

	for (auto& [key, tile] : jsonData["Tiles"].items())
	{
		unsigned int tag = tile.value("tag", -1);
		std::string id = tile.value("id", "");
		sf::Vector2f pos = { tile["position"].value("x",0.f), tile["position"].value("y",0.f) };
		sf::Vector2f scale = { tile["scale"].value("width",1.f), tile["scale"].value("height",1.f) };

		pos.x -= scene->GetWindowWidth() / 2;
		pos.y -= scene->GetWindowHeight() / 2;

		if (tag == 10)
		{
			TileBlock* newTile = scene->CreateEntity<TileBlock>(AssetManager::getInstance().CreateTile(id));
			newTile->SetTag(tag);
			newTile->SetScale(scale);
			newTile->SetPosition(pos.x, pos.y, 0.0f, 0.0f);
			newTile->SetRigidBody(true);
			m_entity.push_back(newTile);
		}
	}
	
	return m_entity;
}

void LevelEditor::SaveLevel()
{
	if (m_gridList.empty())
	{
		Debug::DebugMessage(Debug::Severity::WARN, "Saving Level", "Can't save level is empty");
		return;
	}

	std::filesystem::path filePath = "../../../level/Level0.json";

	int i = 0;
	while (std::filesystem::exists(filePath))
	{
		i++;
		filePath = "../../../level/Level" + std::to_string(i) + ".json";
	}


	json data;
	data["Data"] = json::array();
	data["Tiles"] = json::array();


	for (auto& pair : m_gridList)
	{
		for (SavedEntity* tile : pair.second)
		{
			sf::Vector2f pos = tile->pos;
			sf::Vector2f scale = tile->entity->GetScale();
			std::string id = tile->entity->GetSpriteData() ? tile->entity->GetSpriteData()->textureID : "None";
			std::string type = "TileBlocks";
			unsigned int tag = tile->entity->GetTag();

			json tileData = {
				{"Type", type},
				{"id", id},
				{"tag",tag},
				{"position", {
					{"x", pos.x + pair.first * (GetWindowWidth() - TILE_SIZE * 4)},
					{"y", pos.y}
				}},
				{"scale",{
					{"width",scale.x},
					{"height",scale.y}
				}}
			};

			data["Tiles"].push_back(tileData);
		}
	}

	std::ofstream file(filePath);
	if (!file.is_open())
		Debug::DebugMessage(Debug::Severity::WARN, "Saving Level", "Can't open file");
	else 
	{
		file << data.dump(4);
		file.close();
		Debug::DebugMessage(Debug::Severity::INFO, "Saving Level", "Level saved as : " + filePath.string());
	}
}

void LevelEditor::EraseCurrentLevel()
{
}

bool LevelEditor::CanPoseTile(float _x, float _y)
{
	if (_x >= (GetWindowWidth() - (4 * TILE_SIZE))) return false;

	return true;
}

void LevelEditor::RemoveGrid(int _grid)
{
	for (SavedEntity* se : m_gridList[_grid])
	{
		se->entity->SetPosition(-5000, -5000);
	}
}

void LevelEditor::ReplaceGrid()
{
	for (SavedEntity* se : m_gridList[currentGrid])
	{
		se->entity->SetPosition(se->pos.x, se->pos.y, 0.0f, 0.0f);
	}
}

void LevelEditor::ReplaceTile()
{
	int i = 1;
	for (Entity* tile : m_SelectionPage[currentSelectionIndex])
	{
		tile->SetPosition(GetWindowWidth() - (3 * TILE_SIZE), i * 128, 0.0f, 0.0f);
		i++;
	}
}

void LevelEditor::RemoveTile(int _index)
{
	for (Entity* tile : m_SelectionPage[_index])
		tile->SetPosition(-5000, -5000);
}

void LevelEditor::IndexMove(int _movement)
{   
	int oldIndex = currentSelectionIndex;
	if (_movement + currentSelectionIndex <= 0) currentSelectionIndex = 0;
	else if (_movement + currentSelectionIndex >= m_SelectionPage.size()) currentSelectionIndex = m_SelectionPage.size() - 1;
	else currentSelectionIndex += _movement;

	if (oldIndex == currentSelectionIndex) return;

	RemoveTile(oldIndex);
	ReplaceTile();
}

void LevelEditor::GridMove(int _movement)
{
	int oldIndex = currentGrid;
	if (_movement + currentGrid <= 0) currentGrid = 0;
	else currentGrid += _movement;

	RemoveGrid(oldIndex);
	ReplaceGrid();
}

std::vector<SavedEntity*> LevelEditor::GetPresentTile(float _x, float _y)
{
	std::vector<SavedEntity*> tilePresent;

	for (SavedEntity* se : m_gridList[currentGrid])
	{
		if (se->entity->IsInside(_x, _y))
			tilePresent.push_back(se);
	}

	return tilePresent;
}

float LevelEditor::GetScale(float size, float target)
{
	float truc = round(size / target) * target;
	return truc / size;
}

//Rest in peace petit ange partis trop tôt tu fut le fruit de dure labeur tout ça pour rien
//float LevelEditor::truc2(float size, float target)
//{
//	float truc = ((int)size % (int)target) >= (target / 2.f) ? target : 0.f;
//	float autreTruc = ((int)size / (int)target) * target + truc;
//	return autreTruc / size;
//}

void LevelEditor::DrawGrid()
{
	int windW = GetWindowWidth();
	int windH = GetWindowHeight();

	int nbrW = round(windW / TILE_SIZE) - 3;
	int nbrH = round(windH / TILE_SIZE) + 1;
	
	for (int i = 0; i < nbrW; ++i)
		Debug::DrawLine(TILE_SIZE * i, 0, TILE_SIZE * i, windH, sf::Color::White);

	for (int j = 0; j < nbrH; ++j)
		Debug::DrawLine(0 ,TILE_SIZE * j, windW - (4 * TILE_SIZE), TILE_SIZE * j, sf::Color::White);
}

void LevelEditor::InitEntity()
{
	//m_entityToPlace.push_back(CreateEntity<BreakablePlatform>(120, 60, sf::Color::Cyan));

	AssetManager& AM = AssetManager::getInstance();

	BreakablePlatform* platform = CreateEntity<BreakablePlatform>(AM.CreateSprite("breakable",0,0,493,440));
	platform->SetScale(GetScale(platform->GetCollider().width, TILE_SIZE) / 2, GetScale(platform->GetCollider().height, TILE_SIZE) / 2);
	platform->SetPosition(-5000, -5000);

	if (m_SelectionPage.empty() || m_SelectionPage.back().size() >= 3)
		m_SelectionPage.emplace_back();

	m_SelectionPage.back().push_back(platform);

	Hook* hook = CreateEntity<Hook>(AM.CreateSprite("poteau"));
	hook->SetPosition(-5000,-5000);

	if (m_SelectionPage.empty() || m_SelectionPage.back().size() >= 3)
		m_SelectionPage.emplace_back();

	m_SelectionPage.back().push_back(hook);


}

void LevelEditor::InitTileBlock()
{
	AssetManager& AM = AssetManager::getInstance();

	for (auto& tileData : AM.GetTileBlockList())
	{
		TileBlock* newTile = CreateEntity<TileBlock>(AM.CreateTile(tileData.first));
		newTile->SetTag(10);
		newTile->GetSprite();
		newTile->SetScale(GetScale(newTile->GetCollider().width, TILE_SIZE) / 2, GetScale(newTile->GetCollider().height, TILE_SIZE) / 2);
		newTile->SetPosition(-5000, -5000);

		if (m_SelectionPage.empty() || m_SelectionPage.back().size() >= 3)
			m_SelectionPage.emplace_back();  //Mystic dark magic vector (vector has function you absolutely don't know what's they are doing but it work it's magic i swear)
		//so it's like push back + ultra premium extra croquette
		m_SelectionPage.back().push_back(newTile);
	}

	if (m_SelectionPage.empty()) return;

	ReplaceTile();
}

void LevelEditor::OnDestroy()
{
	pEntitySelected = nullptr;

	for (auto& page : m_SelectionPage)
	{
		for (Entity* e : page)
			e->Destroy();
		page.clear();
	}
	m_SelectionPage.clear();

	for (Entity* tileP : m_posedBlock)
		tileP->Destroy();
	m_posedBlock.clear();

	for (Button* btn : btnList)
		btn->Destroy();
	btnList.clear();
}

void LevelEditor::OnInitialize()
{
	InitTileBlock();
	InitEntity();

	Button* btn1 = CreateEntity<Button>(100, 40, sf::Color::Yellow);
	btn1->SetPosition(GetWindowWidth() - 3 * TILE_SIZE, TILE_SIZE,0.f, 0.f);
	btn1->SetFunction(
		[this]() {
			SaveLevel();
		});
	btnList.push_back(btn1);

	Button* btn2 = CreateEntity<Button>(80, 40, sf::Color::White);
	btn2->SetPosition(GetWindowWidth() - 4 * TILE_SIZE, GetWindowHeight() - TILE_SIZE, 0.f, 0.f);
	btn2->SetFunction(
		[this]() {
			IndexMove(-1);
		}
	);
	btnList.push_back(btn2);

	Button* btn3 = CreateEntity<Button>(80, 40, sf::Color::White);
	btn3->SetPosition(GetWindowWidth() - 2 * TILE_SIZE, GetWindowHeight() - TILE_SIZE, 0.f, 0.f);
	btn3->SetFunction(
		[this]() {
			IndexMove(1);
		});
	btnList.push_back(btn3);

	Button* btn4 = CreateEntity<Button>(80, 40, sf::Color::Cyan);
	btn4->SetPosition(GetWindowWidth() - 4 * TILE_SIZE, GetWindowHeight() - 2 * TILE_SIZE, 0.f, 0.f);
	btn4->SetFunction(
		[this]() {
			GridMove(-1);
		}
	);
	btnList.push_back(btn4);

	Button* btn5 = CreateEntity<Button>(80, 40, sf::Color::Cyan);
	btn5->SetPosition(GetWindowWidth() - 2 * TILE_SIZE, GetWindowHeight() - 2 * TILE_SIZE, 0.f, 0.f);
	btn5->SetFunction(
		[this]() {
			GridMove(1);
		});
	btnList.push_back(btn5);
}

void LevelEditor::OnEvent(const sf::Event& event)
{

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{

		for (Entity* e : m_SelectionPage[currentSelectionIndex])
			TrySetSelectedEntity(e, event.mouseButton.x, event.mouseButton.y);

		for (auto& tile : m_gridList[currentGrid])
			TrySetSelectedEntity(tile->entity, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		int posX = (int)event.mouseButton.x;
		int posY = (int)event.mouseButton.y;

		if (pEntitySelected != nullptr)
		{
			for(SavedEntity* tile  : GetPresentTile(posX, posY))
			{
				if (tile->entity->IsSameTexture(pEntitySelected))
				{
					tile->entity->Destroy();

					m_gridList[currentGrid].erase(
						std::remove(m_gridList[currentGrid].begin(), m_gridList[currentGrid].end(), tile),  //Really the guy who invented std::remove & remove_if go fuck yourself i never understand how the fuck does it works it's dark magic at this level
						m_gridList[currentGrid].end());

					//m_posedBlock.erase(
					//	std::remove(m_posedBlock.begin(), m_posedBlock.end(), tile),  //Really the guy who invented std::remove & remove_if go fuck yourself i never understand how the fuck does it works it's dark magic at this level
					//	m_posedBlock.end());
					Debug::DebugMessage(Debug::Severity::DEBUG, "Tile", "Deleted Tile");
					if (tile->entity == pEntitySelected) pEntitySelected = nullptr;
					return;
				}
			}
			
			if(CanPoseTile(posX,posY)) CreateEntityCopy(pEntitySelected, (posX / (int)TILE_SIZE) * TILE_SIZE, (posY / (int)TILE_SIZE) * TILE_SIZE);
		}

		//Look at mom a if cascade isn't beautifull ? 
		// Yes my son it's beautifull.
		//Why he did this way ?
		//Because is brain melted my son that's why
		//And does it work ?
		//No my son... the sprite become nullptr
		//And did it fix it
		//Yes he did and now it work :D
	}
}

void LevelEditor::OnUpdate()
{
	Debug::DrawText(GetWindowWidth() - 3 * TILE_SIZE, TILE_SIZE, "Save", sf::Color::Black);
	Debug::DrawText(GetWindowWidth() - 4 * TILE_SIZE, GetWindowHeight() - TILE_SIZE, "Prev", sf::Color::Black);
	Debug::DrawText(GetWindowWidth() - 2 * TILE_SIZE, GetWindowHeight() - TILE_SIZE, "Next", sf::Color::Black);
	Debug::DrawText(GetWindowWidth() - 4 * TILE_SIZE, GetWindowHeight() - 2 * TILE_SIZE, "Prev", sf::Color::Black);
	Debug::DrawText(GetWindowWidth() - 2 * TILE_SIZE, GetWindowHeight() - 2 * TILE_SIZE, "Next", sf::Color::Black);

	if (InputManager::Get().IsKeyPressed(sf::Keyboard::Key::A))
		drawGrid = !drawGrid;

	if(drawGrid) DrawGrid();

	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}

void LevelEditor::TrySetSelectedEntity(Entity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void LevelEditor::CreateEntityCopy(Entity* _entity, int _x, int _y)
{
	Entity* newEntity = _entity->Clone();
	newEntity->SetPosition(_x, _y, 0.0f, 0.0f);
	//m_posedBlock.push_back(newEntity);

	m_gridList[currentGrid].push_back(new SavedEntity(newEntity, newEntity->GetPosition(0.0f, 0.0f)));
}