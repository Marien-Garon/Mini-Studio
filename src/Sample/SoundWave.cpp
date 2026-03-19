#include "SoundWave.h"
#include "Enemy.h"
#include <iostream>

void AttackZone::OnInitialize()
{
	m_damage = 1;
	SetSpeed(1000);
	SetMoveAble(true);

}

void AttackZone::OnUpdate()
{
	m_lifeSpan -= GetDeltaTime();

	if (m_lifeSpan <= 0)
		Destroy();
}

void AttackZone::OnCollision(Entity* other)
{
	if (other->IsTag(2))
	{
		static_cast<Enemy*>(other)->TakeDamage(m_damage);
		Destroy();
	}
}
