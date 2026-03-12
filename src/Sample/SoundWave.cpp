#include "SoundWave.h"
#include "Enemy.h"
#include <iostream>

void SoundWave::OnInitialize()
{
	m_damage = 1;
	SetSpeed(1000);
	SetMoveAble(true);
	
}

void SoundWave::OnUpdate()
{
	if (GetPosition().x > GetScene()->GetWindowWidth())
	{
		std::cout << "Soundwave detruite" << std::endl;
		Destroy();
	}
		
}

void SoundWave::OnCollision(Entity* other)
{
	if (other->IsTag(2))
	{
		static_cast<Enemy*>(other)->TakeDamage(m_damage);
	}
}
