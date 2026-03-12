#pragma once
#include "Entity.h"

class PhysicalEntity :
    public Entity
{
private:
    float gravityAcceleration = 9.81f;
    float mGravitySpeed = 0;

    bool isFalling = false;
    bool isJumping = false;

    virtual void Update() override;
protected:

    int jumpSize = 50;

public:     

    virtual void OnUpdate() override {};

    float GetGravitySpeed() { return mGravitySpeed; }
    //#TO DO => RigidBody not under
    bool CanFall();

    bool IsFalling() { return isFalling; }
    void Fall( float deltaTime );
    void StopFall();

    //#TO DO => RigidBody under
    bool CanJump();
    void Jump();

    void SetJumpSize(int newJumpSize) { jumpSize = newJumpSize; }
};

