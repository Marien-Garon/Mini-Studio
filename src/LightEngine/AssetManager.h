#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <filesystem>
#include <fstream>

#include <unordered_map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct TextureData
{
	sf::Texture texture;
	std::string id;
	int fWitdh;
	int fHeight;
};


class AssetManager
{
private:

	std::unordered_map<std::string, TextureData> m_textureList;

public:


	static AssetManager& getInstance() {
		static AssetManager instance;
		return instance;
	}

	bool InitTextureInDirectory(const std::filesystem::path& filename = "../../../assets/textures");

	sf::Texture GetTexture(std::string _id);
	sf::Sprite LoadSprite(std::string _id);
};