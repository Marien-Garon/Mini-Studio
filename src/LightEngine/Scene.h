#pragma once

class GameManager;
class Camera;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "AssetManager.h"

class Scene
{
private:
	GameManager* mpGameManager;

private:
	
protected:

	Camera* mCamera;

	virtual void OnDestroy() {};
	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:

	Scene() = default;
	~Scene();

	template<typename T>
	T* CreateEntity(float width, float height, const sf::Color& color);

	template<typename T>
	T* CreateEntity(SpriteData* _sprite);

	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;
	Camera* GetCamera() { return mCamera; };

	void DrawSprite(sf::Sprite* _sprite) const;

	friend GameManager;

	GameManager* GetGameManager() { return mpGameManager; };
};

#include "Scene.inl"