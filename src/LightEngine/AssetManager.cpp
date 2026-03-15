#include "AssetManager.h"
#include "Debug.h"


void Animation::NextFrame()
{
    currentFrames += 1;
    if (currentFrames >= frameNbr)
    {
        if (loop) currentFrames = 0;
        else currentFrames = frameNbr - 1;
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
        Debug::DebugMessage(Debug::Severity::ERROR, "Find Directory", "Couldn't open directory : " + filename.string());
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "File" + entry.path().filename().string() + " is not a valid file");
            continue;
        }


        if (entry.path().extension() != ".png")
        {
            if (entry.path().extension() != ".json") 
                Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Extension " + entry.path().extension().string() + " is not a valid extension");
            continue;
        }

        std::string id = entry.path().stem().string();

        if (m_tileList.contains(id)) //Only name ?
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Already a tile register at id : " + entry.path().stem().string());
            continue;
        }
        
        TextureData& data = m_tileList[id];

        data.texture.loadFromFile(entry.path().string());
        data.spritesheet = false;
        data.sizeW = data.texture.getSize().x;
        data.sizeH = data.texture.getSize().y;
        Debug::DebugMessage(Debug::Severity::INFO, "Register Tile", "Successfully register : " + id);
    }
}

bool AssetManager::InitMusicInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        Debug::DebugMessage(Debug::Severity::ERROR, "Find Directory", "Couldn't open directory : " + filename.string());
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "File" + entry.path().filename().string() + " is not a valid file");
            continue;
        }


        if (entry.path().extension() != ".ogg")
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Extension" + entry.path().extension().string() + " is not a valid extension");
            continue;
        }

        std::string id = entry.path().stem().string();

        m_musicList[id] = entry.path().string();
        Debug::DebugMessage(Debug::Severity::INFO, "Register music", "Successfully register : " + id);
    }
}


bool AssetManager::InitSoundInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        Debug::DebugMessage(Debug::Severity::ERROR, "Find Directory", "Couldn't open directory : " + filename.string());
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "File" + entry.path().filename().string() + " is not a valid file");
            continue;
        }


        if (entry.path().extension() != ".wav")
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Extension" + entry.path().extension().string() + " is not a valid extension");
            continue;
        }

        if (!m_soundBuffers[entry.path().stem().string()].loadFromFile(entry.path().string())) //Only name ?
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Extension" + entry.path().extension().string() + " is not a valid extension");
            continue;
        }
    }


    for (auto& pair : m_soundBuffers)
    {
        Debug::DebugMessage(Debug::Severity::INFO, "Register sound", "Successfully register : " + pair.first);
    }

    return true;
}

bool AssetManager::InitTextureInDirectory(const std::filesystem::path& filename)
{
    if (!std::filesystem::exists(filename) || !std::filesystem::is_directory(filename)) {
        Debug::DebugMessage(Debug::Severity::ERROR, "Find Directory", "Couldn't open directory : " + filename.string());
        return false;
    }

    for (auto& entry : std::filesystem::directory_iterator(filename))
    {
        if (!entry.is_regular_file())
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "File" + entry.path().filename().string() + " is not a valid file");
            continue;
        }

        if (entry.path().extension() != ".png")
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load File", "Extension" + entry.path().extension().string() + " is not a valid extension");
            continue;
        }

        std::string imgPath = entry.path().string();
        std::string jsonPath = imgPath.substr(0, imgPath.size() - 4) + ".json";

        std::ifstream jsonFile(jsonPath);


        if(!jsonFile.is_open()) 
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load JSON", "Can't open JSON file : " + jsonPath);
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
                Animation& a = data.animations[name];
                a.loop = anim.value("loop", false);

                a.line = anim["line"];
                a.frameNbr = anim["frameNbr"];
                a.duration = anim["duration"];

                //for (auto frame : anim["frames"])
                //    a.frames.push_back(frame);
            }
        }

        TextureData& data = m_textureList[id];

        if (!data.texture.loadFromFile(imgPath))
        {
            Debug::DebugMessage(Debug::Severity::WARN, "Load Texture", "Failed to load texture : " + id);
        }
    }

    for (auto& pair : m_textureList)
    {
        Debug::DebugMessage(Debug::Severity::INFO, "Register texture", "Successfully register : " + pair.first);
    }


    return true;
}

TextureData* AssetManager::GetTextureData(std::string _id)
{
    if (!m_textureList.contains(_id)) return nullptr;
    return &m_textureList[_id];
}

TextureData* AssetManager::GetTileData(std::string _id)
{
    if (!m_tileList.contains(_id)) return nullptr;
    return &m_tileList[_id];
}

sf::Texture AssetManager::GetTexture(std::string _id)
{
    if (!m_textureList.contains(_id)) return sf::Texture();
    return m_textureList[_id].texture;
}

SpriteData* AssetManager::CreateSprite(std::string _id, int _posX, int _posY, int _w, int _h)
{
    return new SpriteData(_id, _posX, _posY, _w, _h);
}

SpriteData* AssetManager::CreateTile(std::string _id)
{
    return new SpriteData(_id, 0,0,0,0, true);
}


sf::Sound* AssetManager::PlaySound(std::string _id)
{
    if (!m_soundBuffers.contains(_id))
    {
        Debug::DebugMessage(Debug::Severity::WARN, "Play Sound", "Not sound at id : " + _id);
        return nullptr;
    }

    sf::Sound* sound = new sf::Sound(m_soundBuffers[_id]);
    sound->play();
    Debug::DebugMessage(Debug::Severity::WARN, "Play Sound", "Play sound : " + _id);
    m_soundPlaying.push_back(sound);
    return sound;
}

sf::Music* AssetManager::PlayMusic(std::string _id)
{
    if (!m_musicList.contains(_id))
    {
        Debug::DebugMessage(Debug::Severity::WARN, "Play music", "Not music at id : " + _id);
        return nullptr;
    };
    
    if (m_musicPlaying != nullptr)
    {
        Debug::DebugMessage(Debug::Severity::INFO, "Play music", "A music is already playing");
        return nullptr;
    }

    sf::Music* music = new sf::Music();
    if (!music->openFromFile(m_musicList[_id]))
    {
        Debug::DebugMessage(Debug::Severity::WARN, "Play music", "Failed to load music");
        return nullptr;
    }

    music->play();
    Debug::DebugMessage(Debug::Severity::INFO, "Play music", "Currently playing : " + _id);
    m_musicPlaying = music;
    return music;
}


sf::Sprite* AssetManager::LoadSprite(std::string _id, int _posX, int _posY, int _w, int _h, bool isTile)
{
    if (!m_textureList.contains(_id) && !m_tileList.contains(_id)) return nullptr;

    if (_w == 0) _w = isTile ? m_tileList[_id].sizeW : m_textureList[_id].sizeW;
    if (_h == 0) _h = isTile ? m_tileList[_id].sizeH : m_textureList[_id].sizeH;

    sf::Texture& texture = isTile ? m_tileList[_id].texture : m_textureList[_id].texture;

    return new sf::Sprite(texture, sf::IntRect(_posX, _posY, _w, _h));
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

AssetManager::~AssetManager()
{
    std::unordered_map<std::string, TextureData> m_textureList;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, std::string> m_musicList;

    std::unordered_map<std::string, TextureData> m_tileList;

    std::vector<sf::Sound*> m_soundPlaying;

    sf::Music* m_musicPlaying = nullptr;

    if (m_musicPlaying != nullptr)
    {
        m_musicPlaying->stop();
        delete m_musicPlaying;
    }

    m_textureList.clear();
    m_soundBuffers.clear();
    m_musicList.clear();

    for (sf::Sound* s : m_soundPlaying)
    {
        s->stop();
        delete s;
    }

}

SpriteData::SpriteData(std::string _id, int _posX, int _posY, int _w, int _h,bool isTile)
{
    if(isTile)
        data = AssetManager::getInstance().GetTileData(_id);
    else
        data = AssetManager::getInstance().GetTextureData(_id);
    textureID = _id;
    sprite = AssetManager::getInstance().LoadSprite(_id, _posX, _posY, _w, _h, isTile);
}

SpriteData::~SpriteData()
{
    delete sprite;
}


void SpriteData::PlayAnimation(const std::string& _id)
{
    playingAnimation = true;
    currentAnimation = _id;
    frameTime = data->animations[currentAnimation].duration;
}

void SpriteData::UpdateAnimation(float deltaTime)
{
    frameTime -= deltaTime;

    if (!playingAnimation) return;
    if (frameTime > 0.0f) return;
    if (!data->animations.contains(currentAnimation)) return;

    Animation& anim = data->animations[currentAnimation];

    frameTime = anim.duration;

    anim.NextFrame();
        
    int posY = anim.line * data->frameSizeH;
    int posX = anim.currentFrames * data->frameSizeW;

    delete sprite;
    sprite = AssetManager::getInstance().LoadSprite(textureID,posX,posY,data->frameSizeW, data->frameSizeH);
}

TextureData::~TextureData()
{
    animations.clear();
}
