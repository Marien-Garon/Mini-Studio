#include "Platform.h"

void Platform::OnInitialize()
{
	SetRigidBody(true);
	SetMoveAble(false);
}

void Platform::OnUpdate()
{
	float dt = GetDeltaTime();

}


