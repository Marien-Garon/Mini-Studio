#pragma once
#include "Platform.h"

class Hook;

class HookPlatform : public Platform
{
private : 
	Hook* m_platformHook;
	int m_direction;

public : 
	void OnInitialize() override;

	void SetPlateformDirection(int direction = 1);
};