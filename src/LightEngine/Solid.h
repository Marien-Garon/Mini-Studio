#pragma once
#include "Entity.h"


class Solid :
    public Entity
{
private:


public:

	virtual void OnUpdate() override{};
	virtual void OnCollision(Entity* collidedWith) override {};
	virtual void OnInitialize() override;
	virtual void OnDestroy() override {};

	virtual bool GoToDirection(int x, int y, float speed = -1.f) {};
	virtual bool GoToPosition(int x, int y, float speed = -1.f) {};
	virtual void SetSpeed(float speed) {};
	virtual float GetSpeed() {};

};

