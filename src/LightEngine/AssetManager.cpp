#include "AssetManager.h"

#include <iostream>


void Animation::Update()
{
    currentFrames += 1;
    if (currentFrames >= frames.size())
    {
        if (loop) currentFrames = 0;
        else currentFrames = frames.size() - 1;
    }
}


void AssetManager::UpdateMusic()
{
    if (m_musicPlaying == nullptr) return;

    if (m_musicPlaying->getStatus() == sf::Music::Stopped)
    {
        delete m_musicPlaying;
        m_musicPlaying = nullptr;
    }
}

void AssetManager::UpdateSounds()
{
    //Look like shit act like shit
    m_soundPlaying.erase(
        std::remove_if(m_soundPlaying.begin(), m_soundPlaying.end(),
            [](sf::Sound* s) { 
                if (s->getStatus() == sf::Sound::Stopped)
                {
                    delete s;
                    return true;
                }

                return false; }),

        m_soundPlaying.end()
    );
}

void AssetManager::UpdateAssets()
{
    UpdateSounds();
    UpdateMusic();
}

bool AssetManager::InitTileInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        std::cout << "path : " << filename << " doesn't exist" << std::endl;
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

        std::string id = entry.path().stem().string();

        if (m_tileList.contains(id)) //Only name ?
        {
            std::cout << "Already a tile register with this name" << std::endl;
            continue;
        }
        
        TextureData& data = m_tileList[id];

        data.texture.loadFromFile(entry.path().string());
    }
}

bool AssetManager::InitMusicInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        std::cout << "path : " << filename << " doesn't exist" << std::endl;
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            std::cout << "Not valid file" << std::endl;
            continue;
        }


        if (entry.path().extension() != ".ogg")
        {
            std::cout << "Not valid extension" << std::endl;
            continue;
        }


        m_musicList[entry.path().stem().string()] = entry.path().string();
        std::cout << entry.path().stem().string() << " register" << std::endl;
    }
}


bool AssetManager::InitSoundInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        std::cout << "path : " << filename << " doesn't exist" << std::endl;
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            std::cout << "Not valid file" << std::endl;
            continue;
        }


        if (entry.path().extension() != ".wav")
        {
            std::cout << "Not valid extension" << std::endl;
            continue;
        }

        if (!m_soundBuffers[entry.path().stem().string()].loadFromFile(entry.path().string())) //Only name ?
        {
            std::cout << "Failed to load the sound" << std::endl;
            continue;
        }
    }


    for (auto& pair : m_soundBuffers)
    {
        std::cout << pair.first << " register" << std::endl;
    }

    return true;
}

bool AssetManager::InitTextureInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        std::cout  << "path : " << filename << " doesn't exist" << std::endl;
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            std::cout << "Not valid file" << std::endl;
            continue;
        }

        if (entry.path().extension() != ".png" && entry.path().extension() != ".PNG")
        {
            std::cout << "Not valid extension" << std::endl;
            continue;
        }

        std::string imgPath = entry.path().string();
        std::string jsonPath = imgPath.substr(0, imgPath.size() - 4) + ".json";

        std::ifstream jsonFile(jsonPath);


        if(!jsonFile.is_open()) {
            std::cout << "Can't open json file" << std::endl;
            continue;
        }

        json jsonData;
        jsonFile >> jsonData;
        jsonFile.close();

        std::string id   = "";

        for (auto& i : jsonData)
        {
            id = i.value("id", imgPath);

            TextureData& data = m_textureList[id];

            data.sizeW       = i["size"].value("width",0);
            data.sizeH       = i["size"].value("height", 0);
            data.spritesheet = i.value("spritesheet", false);

            if (!data.spritesheet)
                continue;

            data.frameSizeW  = i["frame_size"].value("width", 0);
            data.frameSizeH  = i["frame_size"].value("height", 0);

            for (auto& [name, anim] : i["animations"].items())
            {
                Animation& a = data.animations["name"];
                a.loop = anim.value("loop", false);

                for (auto frame : anim["frames"])
                    a.frames.push_back(frame);
            }
        }

        TextureData& data = m_textureList[id];

        if (!data.texture.loadFromFile(imgPath))
            std::cout << "Failed to load texture at path : " <<  imgPath << std::endl;
    }

    for (auto& pair : m_textureList)
    {
        std::cout << pair.first << " register" << std::endl;
    }


    return true;
}

sf::Texture AssetManager::GetTexture(std::string _id)
{
    if (!m_textureList.contains(_id)) return sf::Texture();
    return m_textureList[_id].texture;
}

sf::Sound* AssetManager::PlaySound(std::string _id)
{
    if (!m_soundBuffers.contains(_id))
    {
        std::cout << "No sound at id : " << _id << std::endl;
        return nullptr;
    }

    sf::Sound* sound = new sf::Sound(m_soundBuffers[_id]);
    sound->play();
    m_soundPlaying.push_back(sound);
    return sound;
}

sf::Music* AssetManager::PlayMusic(std::string _id)
{
    if (!m_musicList.contains(_id))
    {
        std::cout << "No music at id : " << _id << std::endl;
        return nullptr;
    };
    
    if (m_musicPlaying != nullptr)
    {
        std::cout << "Music already playing" << std::endl;
        return nullptr;
    }

    sf::Music* music = new sf::Music();
    if (!music->openFromFile(m_musicList[_id]))
    {
        std::cout << "Failed to load music" << std::endl;
        return nullptr;
    }

    music->play();

    m_musicPlaying = music;
    return music;
}


sf::Sprite* AssetManager::LoadSprite(std::string _id, int _posX, int _posY, int _w, int _h)
{
    if (!m_textureList.contains(_id)) return nullptr;

    if (_w == 0) _w = m_textureList[_id].sizeW;
    if (_h == 0) _h = m_textureList[_id].sizeH;

    return new sf::Sprite(m_textureList[_id].texture, sf::IntRect(_posX, _posY, _w, _h));
}

void AssetManager::PauseMusic()
{
    if (m_musicPlaying == nullptr) return;

    m_musicPlaying->pause();
}

void AssetManager::ResumeMusic()
{
    if (m_musicPlaying == nullptr) return;

    m_musicPlaying->play();
}

void AssetManager::StopMusic()
{
    if (m_musicPlaying == nullptr) return;

    m_musicPlaying->stop();
}

void AssetManager::SetSoundVolume(float _volume)
{
    for (sf::Sound* sound : m_soundPlaying)
    {
        sound->setVolume(_volume);
    }
}

void AssetManager::SetMusicVolume(float _volume)
{
    if (m_musicPlaying == nullptr) return;

    m_musicPlaying->setVolume(_volume);
}