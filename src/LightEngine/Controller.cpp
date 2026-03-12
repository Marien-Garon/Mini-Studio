#include "Controller.h"

#include <iostream>

//Replaced with EventType in InputManager
void Controller::UpdateController()
{
	m_isConnected = sf::Joystick::isConnected(m_id);
}

void Controller::SetPressed(Button _btn, bool _value)
{
	m_controllerPressed[_btn] = _value;
}

void Controller::SetHeld(Button _btn, bool _value)
{
	m_controllerHeld[_btn] = _value;
}

void Controller::SetReleased(Button _btn, bool _value)
{
	m_controllerReleased[_btn] = _value;
}

bool Controller::IsControllerPressed(Button _btn)
{
	if (!m_controllerPressed.contains(_btn)) return false;

	return m_controllerPressed[_btn];
}

bool Controller::IsControllerReleased(Button _btn)
{
	if (!m_controllerReleased.contains(_btn)) return false;

	return 	m_controllerReleased[_btn];
}

bool Controller::IsControllerHeld(Button _btn)
{
	if (!m_controllerHeld.contains(_btn)) return false;

	std::cout << "held" << std::endl;

	return 	m_controllerHeld[_btn];
}

void Controller::Reset()
{
	m_controllerPressed.clear();
	m_controllerReleased.clear();
}

void Controller::Disconnect()
{
	m_isConnected = false;
	m_controllerPressed.clear();
	m_controllerReleased.clear();
	m_controllerHeld.clear();
}

void Controller::Connect()
{
	m_isConnected = true;
}