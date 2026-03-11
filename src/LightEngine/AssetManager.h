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

struct Animation
{
	std::vector<int> frames;
	bool loop;
	int currentFrames = 0;

	void Update();
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
};


class AssetManager
{
private:

	std::unordered_map<std::string, TextureData> m_textureList;
	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::unordered_map<std::string, std::string> m_musicList;

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

	bool InitMusicInDirectory(const std::filesystem::path& filename = "../../../assets/musics");
	bool InitSoundInDirectory(const std::filesystem::path& filename = "../../../assets/sounds");
	bool InitTextureInDirectory(const std::filesystem::path& filename = "../../../assets/textures");

	/// <summary>
	/// Return texture with id
	/// </summary>
	/// <param name="_id"></param>
	/// <returns></returns>
	sf::Texture GetTexture(std::string _id);
	sf::Sprite LoadSprite(std::string _id, int _posX = 0, int _posY = 0, int _w = 0, int _h = 0);

	/// <summary>
	/// Play the sound with id
	/// </summary>
	/// <param name="_id -> std::string"></param>
	/// <returns></returns>
	sf::Sound* PlaySound(std::string _id);
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


	//void PauseSound(std::string _id);
	//void StopSound(std::string _id);
	//void ResumeSound(std::string _id);
};