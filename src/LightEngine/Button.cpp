#include "Button.h"
#include <iostream>
#include "InputManager.h"
//void Button::UpdateEvent(const sf::Event& _event)
//{
//	if (_event.type == sf::Event::MouseMoved)
//	{
//		if (IsInside(_event.mouseMove.x, _event.mouseMove.y))
//			isHover = true;
//		else
//			isHover = false;
//	}
//
//	if (_event.type == sf::Event::MouseButtonPressed &&
//		_event.mouseButton.button == sf::Mouse::Left &&
//		IsInside(_event.mouseButton.x, _event.mouseButton.y))
//		Click();
//}

void Button::OnUpdate()
{
	InputManager& IM = InputManager::Get();

	if (!IsInside(IM.GetMousePos().x, IM.GetMousePos().y))
		SetOpacity(255);
	else
		SetOpacity(120);

	if (IsInside(IM.GetMouseClickPos().x, IM.GetMouseClickPos().y))
	{
		if(IM.IsMousePressed(sf::Mouse::Left)) hasBeenClick = true;
	}

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
