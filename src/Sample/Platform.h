#pragma once
#include "Entity.h"

class Platform : public Entity {
public:
    virtual ~Platform() {};

    
    virtual void OnUpdate(float dt);

    
    virtual void OnPlayerContact() = 0;
};