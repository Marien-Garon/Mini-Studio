#include "Bullet.h"
#include "Camera.h"

void Bullet::SetDirection(float dx, float dy, float speed)
{
	m_direction = sf::Vector2f(dx, dy);
	m_speed = speed;
}

void Bullet::OnInitialize()
{

}

void Bullet::OnUpdate()
{
	if (!m_isAlive)
		return;

	float dt = GetDeltaTime();

	sf::Vector2f pos = GetPosition();
	pos.x += m_direction.x * m_speed * dt;
	pos.y += m_direction.y * m_speed * dt;
	SetPosition(pos.x, pos.y);

	Camera* cam = GetScene()->GetCamera();
	sf::Vector2f center = cam->GetView()->getCenter();

	float windW = GetScene()->GetWindowWidth();
	float windH = GetScene()->GetWindowHeight();

	if (GetPosition().x > center.x + windW
		|| GetPosition().y > center.y + windH
		|| GetPosition().x < center.x - windW
		|| GetPosition().y < center.y - windH)
		Destroy();

}

void Bullet::DestroyBullet()
{
	m_isAlive = false;
	Destroy();
}
