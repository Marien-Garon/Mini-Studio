#include "Background.h"
#include "SampleScene.h"

void Background::OnUpdate()
{
	if (GetPosition(1.f, 0.f).x == 0.f) {
		SetPosition(2545.f, 0, 0.f, 0.f);
	}
}