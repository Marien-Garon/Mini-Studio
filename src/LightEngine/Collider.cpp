#include "Collider.h"

#include <iostream>

bool AABBCollider::IsColliding(const AABBCollider& _other)
{
    return (x <= _other.x + _other.width && x + width >= _other.x && y <= _other.y + _other.height && y + height >= _other.y);
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
    if (IsInside(_other)) return Side::INSIDE;


    //Temporary because i don't like this way
    if ((int)_other.x + (int)_other.width <= (int)x) return Side::LEFT;
    if ((int)_other.x >= (int)x + (int)width) return Side::RIGHT;
    if ((int)_other.y >= (int)y + (int)height) return Side::DOWN;
    if ((int)_other.y + (int)_other.height <= (int)y) return Side::UP;

    return Side::NONE;
}
