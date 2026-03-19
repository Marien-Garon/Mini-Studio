#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private :
	int m_damage = 1;

public:

    void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* collidewith) override;

};