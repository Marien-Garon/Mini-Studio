#pragma once
#include "Entity.h"

class SoundBlast : public Entity
{
private:

	int m_damage;
public:

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;


};