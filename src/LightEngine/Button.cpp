#include "Button.h"
#include <iostream>

void Button::UpdateEvent(const sf::Event& _event)
{
	if (_event.type == sf::Event::MouseMoved)
	{
		if (IsInside(_event.mouseMove.x, _event.mouseMove.y))
			isHover = true;
		else
			isHover = false;
	}

	if (_event.type == sf::Event::MouseButtonPressed &&
		_event.mouseButton.button == sf::Mouse::Left &&
		IsInside(_event.mouseButton.x, _event.mouseButton.y))
		Click();
}

void Button::OnUpdate()
{
	if (isHover)
		SetOpacity(120);
	else
		SetOpacity(255);

	if (m_onClick && hasBeenClick)
	{
		m_onClick();
		hasBeenClick = false;
	}
}

void Button::OnInitialize()
{
	SetMoveAble(false);
	SetRigidBody(false);
}
