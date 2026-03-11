#pragma once
#include "Entity.h"
#include"SFML/Graphics/View.hpp"


class Camera :
	public Entity
{
public: 
	sf::View camera;

protected:
	virtual void OnCollision(Entity* collidedWith) override {};
	virtual void OnInitialize() override;
	virtual void OnDestroy() override {};
public: 
	virtual void OnUpdate() override;



};

