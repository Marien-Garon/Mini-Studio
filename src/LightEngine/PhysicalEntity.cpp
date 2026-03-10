#include "PhysicalEntity.h"


void PhysicalEntity::OnUpdate()
{
	if (isFalling == true)
		GoToDirection(GetPosition().x/* + mTarget.position.x*/, GetPosition().y + mTarget.position.y, mGravitySpeed);
	
}

bool PhysicalEntity::CanFall()
{
	return false;
}

/// <summary>Dans PhysicalEntity.
/// <para>Augmente la vitesse de mouvement vers un y >.</para>
/// <para>Pour arreter la chute, appeler StopFall().</para>
/// <seealso cref="PhysicalEntity::StopFall()"/>
/// </summary>
void PhysicalEntity::Fall(float deltaTime)
{
	mGravitySpeed += gravityAcceleration * (deltaTime + 0.5);
	mTarget.position.y += mGravitySpeed * (deltaTime + 0.5);

	isFalling = true;
}

/// <summary>Dans PhysicalEntity.
/// <para>Arrete la chute liée à Fall(). mGravitySpeed = 0</para>
/// <seealso cref="PhysicalEntity::Fall()"/>
/// </summary>
void PhysicalEntity::StopFall()
{
	mGravitySpeed = 0;
	mTarget.position.x = 0;
	mTarget.position.y = 0;

	GoToPosition(GetPosition().x, GetPosition().y, mGravitySpeed);

	isFalling = false;
}


void PhysicalEntity::Jump()
{
	if (isFalling == true)
		return;
	mGravitySpeed = -100;
	mTarget.position.x = 0;
	mTarget.position.y = 0;
}
