#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>


class Controller
{
public:

	enum class Button
	{
		A,
		B,
		X,
		Y,
		LB,
		RB,
		START,
		MENU,
		JOYSTICK_L,
		JOYSTICK_R
	};

private:

	std::unordered_map<Button, bool> m_controllerPressed;
	std::unordered_map<Button, bool> m_controllerHeld;
	std::unordered_map<Button, bool> m_controllerReleased;


	bool m_isConnected = false;
	unsigned int m_id;

public:



	Controller(unsigned int _id) :
		m_id(_id)
	{ 
		m_isConnected = sf::Joystick::isConnected(_id);
	}

	void UpdateController();

	void SetPressed(Button _btn, bool _value);
	void SetHeld(Button _btn, bool _value);
	void SetReleased(Button _btn, bool _value);

	bool IsControllerPressed(Button _btn);
	bool IsControllerReleased(Button _btn);
	bool IsControllerHeld(Button _btn);


	float GetJoystickLeftX() { return sf::Joystick::getAxisPosition(m_id, sf::Joystick::Axis::X); }
	float GetJoystickLeftY() { return sf::Joystick::getAxisPosition(m_id, sf::Joystick::Axis::Y); }

	float GetJoystickRightX() { return sf::Joystick::getAxisPosition(m_id, sf::Joystick::Axis::U); }
	float GetJoystickRightY() { return sf::Joystick::getAxisPosition(m_id, sf::Joystick::Axis::V); }


	float GetTriggerLvl() { return sf::Joystick::getAxisPosition(m_id, sf::Joystick::Axis::Z); };

	void Connect();
	void Disconnect();
	bool IsConnected() { return m_isConnected; };
	void Reset();
};