#include "LevelEditor.h"
#include "AssetManager.h"

#include <iostream>

#define TILE_SIZE 64.f

void LevelEditor::SaveLevel()
{
}

void LevelEditor::EraseCurrentLevel()
{
}

bool LevelEditor::CanPoseTile(float _x, float _y)
{
	for (TileBlock* tile : m_posedBlock)
	{
		if (tile->IsInside(_x, _y)) return false;
	}

	return true;
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

void LevelEditor::InitTileBlock()
{
	AssetManager& AM = AssetManager::getInstance();

	int i = 1;
	for(auto& tileData : AM.GetTileBlockList())
	{ 
		TileBlock* newTile = CreateEntity<TileBlock>(AM.CreateTile(tileData.first));
		newTile->SetTag(10);
		newTile->SetSpriteScale(GetScale(newTile->GetCollider().width, TILE_SIZE), GetScale(newTile->GetCollider().height, TILE_SIZE));
		newTile->SetPosition(100 * i, 200, 0.0f, 0.0f);
		m_tileList.push_back(newTile);
		i++;
	}
}

void LevelEditor::OnInitialize()
{
	InitTileBlock();
}

void LevelEditor::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		for (auto& e : m_entityToPlace)
			TrySetSelectedEntity(e, event.mouseButton.x, event.mouseButton.y);
		for (auto& tile : m_tileList)
			TrySetSelectedEntity(tile, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		int posX = (int)event.mouseButton.x;
		int posY = (int)event.mouseButton.y;

		m_posedBlock.size();

		if (pEntitySelected != nullptr && CanPoseTile(posX, posY))
			CreateEntityCopy(pEntitySelected,(posX / (int)TILE_SIZE) * TILE_SIZE, (posY / (int)TILE_SIZE) * TILE_SIZE);
	}
}

void LevelEditor::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
	m_posedBlock.size();
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