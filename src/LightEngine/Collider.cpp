#include "Collider.h"
#include <iostream>


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
    return (x <= _other.x + _other.width && x + width >= _other.x && y <= _other.y + _other.height && y + height >= _other.y);
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

    //Idk if it work but yeah there is this way i think
    float overlapX1 = (_other.x + _other.width) - x;
    float overlapX2 = (x + width) - _other.x;
    float overlapY1 = (_other.y + _other.height) - y;
    float overlapY2 = (y + height) - _other.y;

    float overlapMin = std::min({ overlapX1, overlapX2, overlapY1, overlapY2 });

    if (overlapMin == overlapX1)   return Side::LEFT;
    if (overlapMin == overlapX2)  return Side::RIGHT;
    if (overlapMin == overlapY1)    return Side::UP;
    if (overlapMin == overlapY2) return Side::DOWN;

    return Side::NONE;
}