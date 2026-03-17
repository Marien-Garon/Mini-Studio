#pragma once
#include "Entity.h"
#include "Player.h"

class Companion : public Entity
{
private :
	Player* mOwner;
public:

	void OnUpdate() override;
	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void Follow();
	void SetOwner(Player* owner);

private:

};

