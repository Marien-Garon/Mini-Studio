#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>

//#include "SceneManager.h"

class Entity;
class Scene;
class Debug;
class Camera;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;
	sf::Image icone;


	//SceneManager sceneManager;
	Scene* mpScene;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

private:
	GameManager();

	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

public:

	void Run();
	sf::RenderWindow* GetWindow() const { return mpWindow; }
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black, bool fullscreen = false);

	template<typename T>
	void LaunchScene();
	void RefreshCamera(Camera* camera);
	void RefreshUI(Camera* camera);

	void DrawSprite(sf::Sprite* _sprite);

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };
	void SetScene(Scene* scene);
	void ClearCurrentSceneEntities();

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"