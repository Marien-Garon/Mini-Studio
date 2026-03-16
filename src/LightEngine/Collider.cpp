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

Side AABBCollider::GetCollisionSide(AABBCollider& _other)
{
    if (IsInside(_other)) return Side::INSIDE;

    bool Point0 = _other.IsInside(x,y);
    bool Point1 = _other.IsInside(x + width, y);
    bool Point2 = _other.IsInside(x, y + height);
    bool Point3 = _other.IsInside(x + width , y + height);

    if (Point0 && Point1)
        return Side::UP;

    if (Point2 && Point3)
        return Side::DOWN;

    if (Point0 && Point2)
        return Side::LEFT;

    if (Point1 && Point3)
        return Side::RIGHT;

    if (Point0)
    {
        if ((_other.x + _other.width) - x < (_other.y + _other.height) - y) return Side::LEFT;
        else return Side::UP;
    }

    if (Point1)
    {
        if ((x + width) -_other.x < (_other.y + _other.height) - y) return Side::RIGHT;
        else return Side::UP;
    }

    if (Point2)
    {
        if ((_other.x + _other.width) - x < (y + height) - _other.y) return Side::LEFT;
        else return Side::DOWN;
    }

    if (Point3)
    {
        if ((x + width) - _other.x < (y + height) - _other.y) return Side::RIGHT;
        else return Side::DOWN;
    }


    //Temporary because i don't like this way YOU SUCKS YA BITCH
    //if ((int)_other.x + (int)_other.width <= (int)x) return Side::LEFT;

    //if ((int)_other.x >= (int)x + (int)width) return Side::RIGHT;

    //if ((int)_other.y >= (int)y + (int)height) return Side::DOWN;

    //if ((int)_other.y + (int)_other.height <= (int)y) return Side::UP;

    return Side::NONE;
}