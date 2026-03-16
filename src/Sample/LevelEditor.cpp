#include "LevelEditor.h"
#include "AssetManager.h"
#include "Debug.h"
#include "Button.h"
#include <iostream>

#define TILE_SIZE 64.f

void LevelEditor::SaveLevel()
{
	if (m_posedBlock.empty())
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

	for (TileBlock* tile : m_posedBlock)
	{
		sf::Vector2f pos = tile->GetPosition(0.f, 0.f);
		std::string id = tile->GetSpriteData()->textureID;
		std::string type = "TileBlocks";

		json tileData = {
			{"Type", type},
			{"id", id},
			{"position", {pos.x, pos.y}}
		};

		data["Tiles"].push_back(tileData);
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

	for (TileBlock* tile : m_posedBlock)
	{
		if (tile->IsInside(_x, _y))
		{
			Debug::DebugMessage(Debug::Severity::DEBUG, "Tile", "A Tile is already present here");
			return false;
		}
	}

	return true;
}

void LevelEditor::ReplaceTile()
{
	int i = 1;
	for (TileBlock* tile : m_page[currentIndex])
	{
		tile->SetPosition(GetWindowWidth() - (3 * TILE_SIZE), i * 128, 0.0f, 0.0f);
		i++;
	}
}

void LevelEditor::RemoveTile(int _index)
{
	for (TileBlock* tile : m_page[_index])
		tile->SetPosition(-5000, -5000);
}

void LevelEditor::IndexMove(int _movement)
{   
	int oldIndex = currentIndex;
	if (_movement + currentIndex <= 0) currentIndex = 0;
	else if (_movement + currentIndex >= m_page.size()) currentIndex = m_page.size() - 1;
	else currentIndex += _movement;

	if (oldIndex == currentIndex) return;

	RemoveTile(oldIndex);
	ReplaceTile();
}

TileBlock* LevelEditor::GetPresentTile(float _x, float _y)
{
	for (TileBlock* tile : m_posedBlock)
	{
		if (tile->IsInside(_x, _y))
			return tile;
	}

	return nullptr;
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
}

void LevelEditor::InitTileBlock()
{
	AssetManager& AM = AssetManager::getInstance();

	for (auto& tileData : AM.GetTileBlockList())
	{
		TileBlock* newTile = CreateEntity<TileBlock>(AM.CreateTile(tileData.first));
		newTile->SetTag(10);
		newTile->GetSprite();
		newTile->SetSpriteScale(GetScale(newTile->GetCollider().width, TILE_SIZE), GetScale(newTile->GetCollider().height, TILE_SIZE));
		newTile->SetPosition(-5000, -5000);

		if (m_page.empty() || m_page.back().size() >= 3)
			m_page.emplace_back();  //Mystic dark magic vector (vector has function you absolutely don't know what's they are doing but it work it's magic i swear)
		//so it's like push back + ultra premium extra croquette
		m_page.back().push_back(newTile);

		m_tileList.push_back(newTile);
	}

	if (m_page.empty()) return;

	ReplaceTile();
}

void LevelEditor::OnDestroy()
{
	pEntitySelected = nullptr;

	for (TileBlock* tile : m_tileList)
		tile->Destroy();
	m_tileList.clear();

	for (Entity* e : m_entityToPlace)
		e->Destroy();
	m_entityToPlace.clear();

	for (TileBlock* tileP : m_posedBlock)
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
	btn1->SetPosition(GetWindowWidth() - 2 * TILE_SIZE, TILE_SIZE);
	btn1->SetFunction(
		[this]() {
			SaveLevel();
		});

	btnList.push_back(btn1);

	Button* btn2 = CreateEntity<Button>(80, 40, sf::Color::White);
	btn2->SetPosition(GetWindowWidth() - 3 * TILE_SIZE, GetWindowHeight() - TILE_SIZE);
	btn2->SetFunction(
		[this]() {
			IndexMove(1);
		}
	);
	btnList.push_back(btn2);

	Button* btn3 = CreateEntity<Button>(80, 40, sf::Color::White);
	btn3->SetPosition(GetWindowWidth() - TILE_SIZE, GetWindowHeight() - TILE_SIZE);
	btn3->SetFunction(
		[this]() {
			IndexMove(-1);
		});
	btnList.push_back(btn3);
}

void LevelEditor::OnEvent(const sf::Event& event)
{
	for (Button* btn : btnList)
	{
		btn->UpdateEvent(event);
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		//3 loop because one is not enough grougrou
		for (auto& e : m_entityToPlace)
			TrySetSelectedEntity(e, event.mouseButton.x, event.mouseButton.y);
		for (auto& tile : m_tileList)
			TrySetSelectedEntity(tile, event.mouseButton.x, event.mouseButton.y);
		for (auto& tile : m_posedBlock)
			TrySetSelectedEntity(tile, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		int posX = (int)event.mouseButton.x;
		int posY = (int)event.mouseButton.y;

		if (pEntitySelected != nullptr)
		{
			if (TileBlock* tile = GetPresentTile(posX, posY))
			{
				if (tile->IsSameTile(static_cast<TileBlock*>(pEntitySelected)))
				{
					tile->Destroy();

					m_posedBlock.erase(
						std::remove(m_posedBlock.begin(), m_posedBlock.end(), tile),  //Really the guy who invented std::remove & remove_if go fuck yourself i never understand how the fuck does it works it's dark magic at this level
						m_posedBlock.end());
					Debug::DebugMessage(Debug::Severity::DEBUG, "Tile", "Deleted Tile");
					if (tile == pEntitySelected) pEntitySelected = nullptr;
				}
			}
			else
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
	DrawGrid();
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
	if (_entity->GetTag() == 10)
	{
		TileBlock* newEntity = static_cast<TileBlock*>(_entity->Clone());
		newEntity->SetPosition(_x, _y, 0.0f, 0.0f);
		m_posedBlock.push_back(newEntity);
	}
}