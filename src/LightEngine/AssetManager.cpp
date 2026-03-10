#include "AssetManager.h"

#include <iostream>

bool AssetManager::InitTextureInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        std::cout << filename << "path doesn't exist " << std::endl;
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            std::cout << "Not valid file" << std::endl;
            continue;
        }

        if (entry.path().extension() != ".png")
        {
            std::cout << "Not valid extension" << std::endl;
            continue;
        }

        TextureData data;
        sf::Texture texture;

        std::string imgPath = entry.path().string();
        std::string jsonPath = imgPath.substr(0, imgPath.size() - 4) + ".json";
        std::ifstream file(jsonPath);

        bool fileExist = file.is_open();

        if(!fileExist) {
            std::cout << "Impossible d'ouvrir le json" << std::endl;
            continue;
        }

        json jsonData;
        file >> jsonData;
        file.close();

        for (auto& i : jsonData)
        {
            data.id = i.value("id", imgPath);
            data.fWitdh = i.value("width", 0);
            data.fHeight = i.value("height", 0);
            std::cout << "loaded all info" << std::endl;
        }
     
        data.texture.loadFromFile(imgPath, sf::IntRect({ 0,0 }, { data.fWitdh, data.fHeight }));
        m_textureList[data.id] = data;
    }

    for (auto pair : m_textureList)
    {
        std::cout << pair.first << " : " << pair.second.fWitdh << std::endl;
    }

    return true;
}

sf::Texture AssetManager::GetTexture(std::string _id)
{
    if (!m_textureList.contains(_id)) return sf::Texture();
    return m_textureList[_id].texture;
}

sf::Sprite AssetManager::LoadSprite(std::string _id)
{
    if (!m_textureList.contains(_id)) return sf::Sprite();
    return sf::Sprite(m_textureList[_id].texture);
}
