#include "Collider.h"

bool IsCollidingAABB(const AABBCollider& _c1, const AABBCollider& _c2)
{
    return (_c1.x < _c2.x + _c2.width && _c1.x + _c1.width > _c2.x && _c1.y < _c2.y + _c2.height && _c1.y + _c1.height > _c2.y);
}

bool IsInsideAABBB(const AABBCollider& _c1, const AABBCollider& _c2)
{
    return ;
}

bool AABBCollider::IsColliding(const AABBCollider& _other)
{
    return (x < _other.x + _other.width && x + width > x && y < _other.y + _other.height && y + height > _other.y);
}

bool AABBCollider::IsInside(const AABBCollider& _other)
{
    return (x > _other.x && x + width < _other.x + _other.width && y > _other.y && y + height <= _other.y + _other.height);
}
