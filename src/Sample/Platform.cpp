#include "Platform.h"

void Platform::OnInitialize()
{
	SetRigidBody(true);
	SetMoveAble(false);
	SetTag(0);
}

void Platform::OnUpdate()
{
	float dt = GetDeltaTime();

}


