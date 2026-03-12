#include "PhysicalEntity.h"

void PhysicalEntity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;

	sf::Vector2f translation = distance * mDirection;
	mShape.move(translation);

	if (mTarget.isSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	if (isJumping == true)
	{
		GoToDirection(GetPosition().x, mTarget.position.y, mGravitySpeed);

		if (GetPosition().y <= mTarget.position.y)
		{
			isJumping = false;
			isFalling = true;
			Fall(dt);
		}
	}
	if (isFalling == true)
	{
		Fall(dt);
		GoToDirection(GetPosition().x, GetPosition().y + mTarget.position.y, mGravitySpeed);
	}


	OnUpdate();
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
	mTarget.position.y += mGravitySpeed * (deltaTime + 1);

	isFalling = true;
}

/// <summary>Dans PhysicalEntity.
/// <para>Arrete la chute liée à Fall(). mGravitySpeed = 0</para>
/// <seealso cref="PhysicalEntity::Fall()"/>
/// </summary>
void PhysicalEntity::StopFall()
{
	mGravitySpeed = 0;
	mTarget.position.y = 0;
	GoToPosition(GetPosition().x, GetPosition().y, mGravitySpeed);

	isFalling = false;
}

bool PhysicalEntity::CanJump()
{
	return false;
}

void PhysicalEntity::Jump()
{
	if (isFalling == true)
		return;

	mGravitySpeed = 100;
	mTarget.position.y = GetPosition().y - jumpSize;

	isJumping = true;
}
