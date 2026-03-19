#include "Bullet.h"
#include "Camera.h"
#include "Player.h"

void Bullet::OnInitialize()
{
	mSpeed = 400.f;
	
}

void Bullet::OnUpdate()
{

	Camera* cam = GetScene()->GetCamera();
	sf::Vector2f center = cam->GetView().getCenter();
	float windW = GetScene()->GetWindowWidth();
	float windH = GetScene()->GetWindowHeight();

	if (GetPosition().x > center.x + windW
		|| GetPosition().y > center.y + windH
		|| GetPosition().x < center.x - windW
		|| GetPosition().y < center.y - windH)
		Destroy();

}

void Bullet::OnCollision(Entity* collidewith)
{
	if (collidewith->IsTag(1))
	{
		static_cast<Player*>(collidewith)->TakeDamage(m_damage);
		Destroy();
	}
		
	if (collidewith->IsTag(0))
		Destroy();
}
