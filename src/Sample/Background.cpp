#include "Background.h"
#include "SampleScene.h"
#include "Camera.h"

void Background::OnUpdate()
{
	sf::Vector2f cameraPos = GetScene<SampleScene>()->GetCamera()->GetView()->getCenter();
	float windowWidth = GetScene<SampleScene>()->GetWindowWidth();

	sf::Vector2f position = GetPosition(1.f, 0.f);

 	if (position.x < 0)
	{
		SetPosition(windowWidth, position.y, 0.f, 0.f);
	}
}