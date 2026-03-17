#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"
#include "iostream"
#include "stdio.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

void Entity::Initialize(float _width, float _height, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	if (!hasSprite)
	{
		mShape.setOrigin(0.f, 0.f);
		mShape.setSize({ _width, _height });
		mShape.setFillColor(color);
	}

	m_collider = { GetPosition(0.0f,0.0f).x, GetPosition(0.0f,0.0f).y, _width, _height};

	mTarget.isSet = false;

	OnInitialize();
}

void Entity::Repulse(Entity* other) 
{
	AABBCollider c1 = GetCollider();
	AABBCollider c2 = other->GetCollider();

	float overlapX1 = (c1.x + c1.width) - c2.x; 
	float overlapX2 = (c2.x + c2.width) - c1.x;
	float overlapY1 = (c1.y + c1.height) - c2.y;
	float overlapY2 = (c2.y + c2.height) - c1.y;

	float moveX = (overlapX1 < overlapX2) ? overlapX1 : -overlapX2;
	float moveY = (overlapY1 < overlapY2) ? overlapY1 : -overlapY2;

	if (std::fabs(moveX) < std::fabs(moveY))
	{
		SetPosition(c1.x - moveX / 2.f, c1.y, 0.0f, 0.0f);
		if (other->IsMoveable()) other->SetPosition(c2.x + moveX / 2.f, c2.y, 0.0f, 0.0f);
	}
	else
	{
		SetPosition(c1.x, c1.y - moveY / 2.f, 0.0f, 0.0f);
		if (other->IsMoveable()) other->SetPosition(c2.x, c2.y + moveY / 2.f, 0.0f, 0.0f);
	}
}

void Entity::StartGravity(float startSpeed)
{
	mGravitySpeed = startSpeed;
	mIsGravity = true;
}

bool Entity::IsColliding(Entity* other)
{
	return m_collider.IsColliding(other->GetCollider());
}

bool Entity::IsInside(float _x, float _y)
{
	return m_collider.IsInside(_x, _y);
}

bool Entity::IsInside(Entity* _other)
{
	return m_collider.IsInside(_other->GetCollider());
}

Side Entity::GetCollidingSide(Entity* _other)
{
	return m_collider.GetCollisionSide(_other->GetCollider());
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::Vector2f size = hasSprite ? sf::Vector2f(m_sprite->getTextureRect().width, m_sprite->getTextureRect().height) : mShape.getSize();

	x -= size.x * ratioX;
	y -= size.y * ratioY;

	if (hasSprite)
		m_sprite->setPosition(x, y);
	else
		mShape.setPosition(x, y);

	m_collider.SetPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

void Entity::SetOpacity(float _alpha)
{
	if (hasSprite) m_sprite->setColor(sf::Color(255, 255, 255, _alpha));
	else
	{
		sf::Color color = mShape.getFillColor();
		mShape.setFillColor(sf::Color(color.r, color.g, color.b, _alpha));
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size = hasSprite ? sf::Vector2f(m_sprite->getTextureRect().width, m_sprite->getTextureRect().height) : mShape.getSize();
	sf::Vector2f position = hasSprite ? m_sprite->getPosition() : mShape.getPosition();

	position.x += size.x * ratioX;
	position.y += size.y * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;

	sf::Vector2f translation = distance * mDirection;
	sf::Vector2f newPos = GetPosition() + translation;

	SetPosition(newPos.x, newPos.y);

	if (mTarget.isSet) 
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	if (mIsGravity)
	{
		mGravitySpeed += mGravityAcceleration * dt;
		float transY = mGravitySpeed * dt;

		sf::Vector2f newPos = GetPosition();
		newPos.y += transY;

		SetPosition(newPos.x, newPos.y);
	}

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

AABBCollider& Entity::GetCollider()
{
	return m_collider;
}
