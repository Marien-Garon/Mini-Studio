#include "SoundBlast.h"
#include "Enemy.h"
#include <iostream>

void SoundBlast::OnInitialize()
{
	m_damage = 3;
	SetSpeed(1000);
	SetMoveAble(true);

}

void SoundBlast::OnUpdate()
{
	if (GetPosition().x > GetScene()->GetWindowWidth())
	{
		std::cout << "SoundBlast detruite" << std::endl;
		Destroy();
	}

}

void SoundBlast::OnCollision(Entity* other)
{
	if (other->IsTag(2))
	{
		static_cast<Enemy*>(other)->TakeDamage(m_damage);
		Destroy();
	}
}
