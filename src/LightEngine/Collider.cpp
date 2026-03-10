#include "Collider.h"

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
    return ( _x > x && _x < x + width && _y > y && y < y + height );
}

void AABBCollider::SetPosition(float _x, float _y)
{
    x = _x;
    y = _y;
}

Side AABBCollider::GetCollisionSide(const AABBCollider& _other)
{
    if (!IsColliding(_other)) return Side::NONE;
    if (IsInside(_other)) return Side::INSIDE;

    if (x > _other.x && _other.x + _other.width <= x) return Side::RIGHT;
    if (x < _other.x && _other.x > x + width) return Side::LEFT;
    if (y < _other.y && _other.y > y + height) return Side::DOWN;
    if (y > _other.y && _other.y + height <= y) return Side::UP;

    return Side::NONE;
}