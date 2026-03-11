#pragma once

#include <SFML/System/Vector2.hpp>
#include "Collider.h"
#include <vector>

class Component;

class NewEntity
{
protected:

	AABBCollider m_collider;

	sf::Vector2f m_pos;
	int m_tag = -1;

	std::vector<Component*> m_componentList;

public:

	void SetPosition(const sf::Vector2f& _pos) { m_pos = _pos; };
	void SetPosition(float _x, float _y) { m_pos.x = _x; m_pos.y = _y; };
	void SetTag(int _tag) { m_tag = _tag; };


	const sf::Vector2f& GetPosition() { return m_pos; };
	int GetTag() { return m_tag; };


	bool IsColliding(NewEntity* other);
	bool IsInside(float _x, float _y);
	bool IsInside(NewEntity* _other);
	Side GetCollidingSide(NewEntity* _other);
	const AABBCollider& GetCollider() { return m_collider; };


protected:

	virtual void OnUpdate() {};
	virtual void OnCollision(NewEntity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};

private:

	void Update();
	void Initialize();
	//void Initialize(float width, float height, const sf::Color& color);
};