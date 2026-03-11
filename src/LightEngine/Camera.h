#pragma once
#include "Entity.h"
#include"SFML/Graphics/View.hpp"


class Camera :
	public Entity
{
public: 
	sf::View camera;

protected:
public: 
	virtual void OnCollision(Entity* collidedWith) override {};
	virtual void OnInitialize() override;
	virtual void OnDestroy() override {};
	virtual void OnUpdate() override;

	void SetupCamera(int cameraSpeed, Entity* entityToFolow);

	sf::View* GetView() { return &camera; }


};

