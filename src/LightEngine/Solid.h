#pragma once
#include "Entity.h"
class Solid :
    public Entity
{
private:




public:
	virtual bool GoToDirection(int x, int y, float speed = -1.f) {}
	virtual bool GoToPosition(int x, int y, float speed = -1.f) {}
	virtual void SetSpeed(float speed) {}
	virtual float GetSpeed() {}

};

