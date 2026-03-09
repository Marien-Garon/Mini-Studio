#pragma once
#include "Entity.h"

class PhysicalEntity :
    public Entity
{
private:
    float gravityAcceleration = 9.81f;
    float mGravitySpeed = 0;

public: 
    void Fall(float deltaTime);

};

