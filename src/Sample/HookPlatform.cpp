#include "HookPlatform.h"
#include "Hook.h"

void HookPlatform::OnInitialize()
{
	m_platformHook = CreateEntity<Hook>(10, 10, sf::Color::Yellow);
	if (m_direction == 1) {
		m_platformHook->SetPosition(GetPosition(0.f, 0.f).x - 10, GetPosition(0.f, 0.f).y - 10);
	}
	else {
		m_platformHook->SetPosition(GetPosition(1.f, 0.f).x + 10, GetPosition(0.f, 0.f).y + 10);
	}
}

void HookPlatform::SetPlateformDirection(int direction)
{
	m_direction = direction;
}
