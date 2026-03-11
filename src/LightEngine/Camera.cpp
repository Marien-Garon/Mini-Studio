#include "Camera.h"
#include <iostream>

void Camera::OnUpdate()
{
	camera.move(sf::Vector2f(mSpeed, 0));
}

void Camera::SetupCamera(int cameraSpeed, Entity* entityToFolow)
{
	mSpeed = cameraSpeed;

	camera.setCenter(entityToFolow->GetPosition().x, entityToFolow->GetPosition().y);
}

void Camera::OnInitialize()
{
	sf::View view2(sf::Vector2f(GetScene()->GetWindowWidth() / 2, GetScene()->GetWindowHeight() / 2), sf::Vector2f(GetScene()->GetWindowWidth(), GetScene()->GetWindowHeight()));
	camera = view2;
}
