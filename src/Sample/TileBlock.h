#pragma once

#include "Entity.h"

class TileBlock : public Entity
{
public:
	
	bool IsSameTile(TileBlock* _tile);


	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;

	Entity* Clone() override;
};
