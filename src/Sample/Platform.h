#pragma once
#include "Entity.h"
#include "PhysicalEntity.h"

class Platform : public Entity 
{
protected:
    AABBCollider collider;
public:
    virtual ~Platform() {};

    virtual void CheckCollision(AABBCollider& playerCollider,PhysicalEntity* player) = 0;
    
    virtual void OnUpdate(float dt);

    
    virtual void OnPlayerContact() = 0;
};