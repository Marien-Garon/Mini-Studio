#include "Mob1.h"
#include "Bullet.h"

void Mob1::Attack()
{
    Bullet* bullet = CreateEntity<Bullet>(AssetManager::getInstance().CreateSprite("mobProj"));
    bullet->SetPosition(GetPosition().x, GetPosition().y);
    bullet->SetDirection(m_directionFacing, 0.f);
}
