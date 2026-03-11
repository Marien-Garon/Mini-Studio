#include "Camera.h"
#include <iostream>

void Camera::OnUpdate()
{
	GoToDirection(GetScene()->GetWindowWidth(), GetPosition().y, mSpeed);

	camera.setCenter(GetPosition().x, GetPosition().y);
	camera.move(100, 100);

}

void Camera::OnInitialize()
{
	mSpeed = 100;

	SetPosition(GetScene()->GetWindowWidth() / 2, GetScene()->GetWindowHeight() / 2);
	SetDirection(GetScene()->GetWindowWidth(), GetScene()->GetWindowHeight() / 2, mSpeed);

	sf::View view2(sf::Vector2f(GetPosition().x, GetPosition().y), sf::Vector2f(GetScene()->GetWindowHeight(), GetScene()->GetWindowWidth()));
	camera = view2;
	
	camera.setSize(200, 200);
}
