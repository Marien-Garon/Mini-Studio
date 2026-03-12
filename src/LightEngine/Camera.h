#pragma once
#include "Entity.h"
#include"SFML/Graphics/View.hpp"


class Camera :
	public Entity
{
public: 
	sf::View camera;
	Entity* followedEntity;

	int rotateCount;

protected:
public: 
	virtual void OnCollision(Entity* collidedWith) override {};
	virtual void OnInitialize() override;
	virtual void OnDestroy() override {};
	virtual void OnUpdate() override;

	void SetupCamera(int cameraSpeed, Entity* entityToFolow);
	void Shake(int degree);

	sf::View* GetView() { return &camera; }


};

