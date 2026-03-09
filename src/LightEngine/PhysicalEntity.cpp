#include "PhysicalEntity.h"

void PhysicalEntity::Fall(float deltaTime)
{
	mGravitySpeed += gravityAcceleration * (deltaTime + 0.5);
	mTarget.position.y += mGravitySpeed * (deltaTime + 0.5);

	GoToDirection(GetPosition().x, GetPosition().y + mTarget.position.y, mGravitySpeed);
}
