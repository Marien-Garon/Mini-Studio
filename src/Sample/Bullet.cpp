#include "Bullet.h"
#include "Camera.h"

void Bullet::OnUpdate()
{
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
