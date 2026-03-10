#include "PhysicalEntity.h"


void PhysicalEntity::OnUpdate()
{
	if (isJumping == true)
	{
		GoToDirection(GetPosition().x, mTarget.position.y, mGravitySpeed);
		if (GetPosition().y <= mTarget.position.y)
		{
			isJumping = false;
			isFalling = true;
			mGravitySpeed = 0;
			Fall(GetDeltaTime());
		}
	}

	if (isFalling == true)
	{
		Fall(GetDeltaTime());
		GoToDirection(GetPosition().x, GetPosition().y + mTarget.position.y, mGravitySpeed);
	}

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
	mGravitySpeed += gravityAcceleration * (deltaTime + 0.2);
	mTarget.position.y += mGravitySpeed * (deltaTime + 0.2);

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
	isJumping = false;
}


void PhysicalEntity::Jump()
{
	if (isFalling == true)
		return;

	mGravitySpeed = 100;
	mTarget.position.x = 0;
	mTarget.position.y = GetPosition().y - jumpSize;

	isJumping = true;
}
