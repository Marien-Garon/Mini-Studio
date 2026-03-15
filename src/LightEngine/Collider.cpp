#include "Collider.h"

AABBCollider::AABBCollider(float _x, float _y, float _w, float _h) :
    x(_x),
    y(_y),
    width(_w),
    height(_h),
    bWidth(_w),
    bHeight(_h)
{ }

bool AABBCollider::IsColliding(const AABBCollider& _other)
{
    return (x < _other.x + _other.width && x + width > _other.x && y < _other.y + _other.height && y + height > _other.y);
}

bool AABBCollider::IsInside(const AABBCollider& _other)
{
    return (x > _other.x && x + width < _other.x + _other.width && y > _other.y && y + height <= _other.y + _other.height);
}

bool AABBCollider::IsInside(float _x, float _y)
{
    return ( _x > x && _x < x + width && _y > y && _y < y + height );
}

void AABBCollider::SetPosition(float _x, float _y)
{
    x = _x;
    y = _y;
}

void AABBCollider::SetScale(float _x, float _y)
{
    width = bWidth * _x;
    height = bHeight * _y;
}

void AABBCollider::SetScale(const sf::Vector2f& _scale)
{
    width = bWidth * _scale.x;
    height = bHeight * _scale.y;
}

Side AABBCollider::GetCollisionSide(const AABBCollider& _other)
{
    if (IsInside(_other)) return Side::INSIDE;

    if (_other.x + _other.width <= x) return Side::LEFT;
    if (_other.x >= x + width) return Side::RIGHT;
    if (_other.y >= y + height) return Side::DOWN;
    if (_other.y + height <= y) return Side::UP;

    return Side::NONE;
}