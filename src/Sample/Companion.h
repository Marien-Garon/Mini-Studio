#pragma once
#include "Entity.h"

class Companion : public Entity
{
private :
	sf::Vector2f m_basePosition;
	int m_ondulation = 30;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};

