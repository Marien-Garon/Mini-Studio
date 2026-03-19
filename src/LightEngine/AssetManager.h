#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


enum class SpriteType
{
	Classic,
	Tile,
	UnderPlatform,
	DecoBlock
};

struct Animation
{
	int line = 0;
	int frameNbr = 0;
	bool loop = false;
	int currentFrames = 0;
	float duration = 0.0f;

	void NextFrame();
};


struct TextureData
{
	sf::Texture texture;
	int sizeW;
	int sizeH;
	int frameSizeW;
	int frameSizeH;
	bool spritesheet;

	std::unordered_map<std::string, Animation> animations;

	~TextureData();
};

struct SpriteData
{
	sf::Sprite* sprite = nullptr;
	TextureData* data = nullptr;

	std::string textureID;

	bool playingAnimation = false;
	float frameTime = 0.f;
	std::string currentAnimation;

	SpriteData(std::string _id, int _posX = 0, int _posY = 0, int _w = 0, int _h = 0, SpriteType _type = SpriteType::Classic);
	~SpriteData();

	void PlayAnimation(const std::string& _id);
	void UpdateAnimation(float deltaTime);
};

/// <summary>
/// Init, store and use all of the assets
/// </summary>
class AssetManager
{
private:

	std::unordered_map<std::string, TextureData> m_textureList;
	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::unordered_map<std::string, std::string> m_musicList;

	std::unordered_map<std::string, TextureData> m_tileList;
	std::unordered_map<std::string, TextureData> m_underPlatformList;
	std::unordered_map<std::string, TextureData> m_decoBlockList;

	std::vector<sf::Sound*> m_soundPlaying;

	sf::Music* m_musicPlaying = nullptr;

	void UpdateMusic();
	void UpdateSounds();

public:

	static AssetManager& getInstance() {
		static AssetManager instance;
		return instance;
	}
	
	void UpdateAssets();

	bool InitDecoBlock(const std::filesystem::path& filename);
	bool InitUnderPlatform(const std::filesystem::path& filename);
	bool InitTileInDirectory(const std::filesystem::path& filename = "../../../assets/tile");
	bool InitMusicInDirectory(const std::filesystem::path& filename = "../../../assets/musics");
	bool InitSoundInDirectory(const std::filesystem::path& filename = "../../../assets/sounds");
	bool InitTextureInDirectory(const std::filesystem::path& filename = "../../../assets/textures");
	
	const std::unordered_map<std::string, TextureData>& GetTileBlockList() { return m_tileList; };
	const std::unordered_map<std::string, TextureData>& GetUnderPlatformList() { return m_underPlatformList; };
	const std::unordered_map<std::string, TextureData>& GetDecoBlocks() { return m_decoBlockList; };

	TextureData* GetTextureData(std::string _id);
	TextureData* GetTileData(std::string _id);
	TextureData* GetUnderPlatformData(std::string _id);
	TextureData* GetDecoBlockData(std::string _id);

	/// <summary>
	/// Return texture with id
	/// </summary>
	/// <param name="_id"></param>
	/// <returns></returns>
	sf::Texture GetTexture(std::string _id);

	/// <summary>
	/// Create a Sprite and return it in the form a SpriteData who contain a pointer for the sprite and the texture
	/// </summary>
	/// <param name="std::string _id : id of the texture"></param>
	/// <param name="int _posX : position in pixel of where the sprite start from the texture"></param>
	/// <param name="int _posY : position in pixel of where the sprite start from the texture"></param>
	/// <param name="int _w : width of the sprite"></param>
	/// <param name="int _h : height of the sprite"></param>
	/// <returns></returns>
	SpriteData* CreateSprite(std::string _id, int _posX = 0, int _posY = 0, int _w = 0, int _h = 0);
	SpriteData* CreateTile(std::string _id, SpriteType _type = SpriteType::Tile);


	/// <summary>
	/// Return a new object Sprite using the texture with the id if it exist if not return a empty Sprite
	/// Can use only a part of the texture use position and size for that
	/// </summary>
	/// <param name="_id -> id of the texture"></param>
	/// <param name="_posX -> Position in the texture you want to start  for create the sprite"></param>
	/// <param name="_posY -> Position in the texture you want to start  for create the sprite"></param>
	/// <param name="_w -> Size of the sprite you want to create from the texture"></param>
	/// <param name="_h -> Size of the sprite you want to create from the texture"></param>
	/// <returns></returns>
	sf::Sprite* LoadSprite(std::string _id, int _posX = 0, int _posY = 0, int _w = 0, int _h = 0, SpriteType _type = SpriteType::Classic);

	/// <summary>
	/// Play the sound with id
	/// </summary>
	/// <param name="_id -> std::string"></param>
	/// <returns></returns>
	sf::Sound* PlaySound(std::string _id);
	/// <summary>
	/// Play a music
	/// </summary>
	/// <param name="stf::string _id : id of the music"></param>
	/// <returns></returns>
	sf::Music* PlayMusic(std::string _id);
	/// <summary>
	/// Pause the music use Resume for replay it
	/// </summary>
	void PauseMusic();
	/// <summary>
	/// Resume music if music is paused or stopped
	/// </summary>
	void ResumeMusic();
	/// <summary>
	/// Stop the music
	/// </summary>
	void StopMusic();
	/// <summary>
	/// Set the volume for the sound the minimum is 0 (no volume) and the maximum is 100
	/// </summary>
	void SetSoundVolume(float _volume = 100.f);
	/// <summary>
	/// Set the volume for the music the minimum is 0 (no volume) and the maximum is 100
	/// </summary>
	void SetMusicVolume(float _volume = 100.f);



	~AssetManager();



	//Rest in peace
	//void PauseSound(std::string _id);
	//void StopSound(std::string _id);
	//void ResumeSound(std::string _id);
};