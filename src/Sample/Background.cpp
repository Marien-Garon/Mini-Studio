#include "Background.h"
#include "SampleScene.h"
#include "Camera.h"

void Background::OnUpdate()
{
	sf::Vector2f cameraPos = GetScene<SampleScene>()->GetCamera()->GetView()->getCenter();
	float windowWidth = GetScene<SampleScene>()->GetWindowWidth();
	if (GetPosition(1.f, 0.f).x == cameraPos.x - (windowWidth / 2)) {
		SetPosition(cameraPos.x + (windowWidth / 2), cameraPos.y, 0.f, 0.5f);
	}
}