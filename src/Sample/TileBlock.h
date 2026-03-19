#pragma once

#include "Platform.h"

class TileBlock : public Platform
{
public:
	
	bool IsSameTile(TileBlock* _tile);


	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void OnInitialize() override;
	void OnDestroy() override;

	Entity* Clone() override;
};
