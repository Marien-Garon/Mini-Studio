#pragma once
#include "Entity.h"
#include"SFML/Graphics/View.hpp"


class Camera :
	public Entity
{
public: 
	sf::View camera;
	Entity* followedEntity;

	sf::View UIView;
	Entity* heart;

	int rotateCount;

public: 
	virtual void OnCollision(Entity* collidedWith) override {};
	virtual void OnInitialize() override;
	virtual void OnDestroy() override {};
	virtual void OnUpdate() override;

	void SetupCamera(int cameraSpeed, Entity* entityToFolow);
	void SetupUICamera(Entity* entityToFolow);

	void AddElementToCamera(Entity* newEntityOnCamera);
	void Shake(int degree);

	sf::View& GetView() { return camera; }
	
	~Camera() = default;

	sf::View& GetUIView() { return UIView; }

};

