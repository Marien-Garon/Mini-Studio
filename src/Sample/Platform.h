#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
    void OnInitialize() override;
    void OnUpdate() override;

    sf::Vector2f GetSize() const { return mShape.getSize(); }
    sf::Vector2f GetTopLeft() const { return mShape.getPosition(); }

	bool IsActive() { return mRigidBody; }
};
