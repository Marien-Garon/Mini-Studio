#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Collider.h"

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:

	AABBCollider m_collider;

	sf::RectangleShape mShape;
	sf::Sprite* m_sprite = nullptr;

    sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;
	bool hasSprite = false;
	bool m_isMoveable = false;

	float gravityAcceleration = 9.81f;
	float mGravitySpeed = 0;

	bool isFalling = false;
	bool isJumping = false;

	int jumpSize = 100;

public:

	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	float GetSpeed() { return mSpeed; }
	void SetTag(int tag) { mTag = tag; }

	bool IsFalling() { return isFalling; }
	void Fall(float deltaTime);
	void StopFall();

	float GetGravitySpeed() { return mGravitySpeed; }
	void SetJumpSize(int newJumpSize) { jumpSize = newJumpSize; }

	//float GetRadius() const { return mShape.getRadius(); }

	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other);
	bool IsInside(float _x, float _y);
	bool IsInside(Entity* _other);
	Side GetCollidingSide(Entity* _other);

	void SetMoveAble(bool _moveable) { m_isMoveable = _moveable; };
	bool IsMoveable() { return m_isMoveable; };

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

	const AABBCollider& GetCollider();

    template<typename T>
    T* CreateEntity(float width, float height, const sf::Color& color);

	template<typename T>
	T* CreateEntity(sf::Sprite* _sprite, const sf::Color& color);

	void SetSprite(sf::Sprite* _sprite) { m_sprite = _sprite; hasSprite = true; };
	void SetSpriteColor(const sf::Color& _color) { m_sprite->setColor(_color); };
	void SetSpriteScale(float _x, float _y) { m_sprite->setScale(_x, _y); };
	void SetSpriteScale(const sf::Vector2f& _scale) { m_sprite->setScale(_scale); };
	void SetSpriteRotation(float _angle) { m_sprite->setRotation(_angle); };

	sf::Sprite* GetSprite() { return m_sprite; };

	bool HasSprite() { return hasSprite; };

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
private:
    virtual void Update();
	void Initialize(float width, float height, const sf::Color& color);
	void Repulse(Entity* other);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"