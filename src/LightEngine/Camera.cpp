#include "Camera.h"
#include <iostream>

void Camera::OnUpdate()
{
	camera.setCenter(camera.getCenter().x, followedEntity->GetPosition().y);
	camera.move(sf::Vector2f(mSpeed, 0));

	if (camera.getRotation() > 0 /*&& GetDeltaTime() >= 0.01667*/)
	{
		camera.rotate(-camera.getRotation()/3);
	}
}

void Camera::SetupCamera(int cameraSpeed, Entity* entityToFolow)
{
	mSpeed = cameraSpeed;
	followedEntity = entityToFolow;

	camera.setCenter(followedEntity->GetPosition().x, followedEntity->GetPosition().y);
}

void Camera::Shake(int degree)
{
	camera.rotate(degree);
}

void Camera::OnInitialize()
{
	sf::View view2(sf::Vector2f(GetScene()->GetWindowWidth() / 2, GetScene()->GetWindowHeight() / 2), sf::Vector2f(GetScene()->GetWindowWidth(), GetScene()->GetWindowHeight()));
	camera = view2;
}
