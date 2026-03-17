#include "InputManager.h"
#include "Debug.h"
#include <iostream>


using EventType = sf::Event::EventType;




void InputManager::HandleMousePressed(const sf::Event& event)
{
	if (m_mouseHeld[event.mouseButton.button])
	{
		m_mousePressed[event.mouseButton.button] = false;
		return;
	}

	m_mousePressed[event.mouseButton.button] = true;
	m_mouseHeld[event.mouseButton.button] = true;
}

void InputManager::HandleKeyPressed(const sf::Event& event)
{
	if (m_keyHeld[event.key.code])
	{
		m_keyPressed[event.key.code] = false;
		return;
	}

	m_keyPressed[event.key.code] = true;
	m_keyHeld[event.key.code] = true;
}

void InputManager::HandleJoystickPressed(const sf::Event& event)
{
	unsigned int id = event.joystickButton.joystickId;
	Controller* controller = m_controllerList[id];
	Controller::Button btn = static_cast<Controller::Button>(event.joystickButton.button);

	if (controller->IsControllerHeld(btn)) 
	{
		controller->SetPressed(btn, false);  //idk wy it doesn't work
		return;
	}

	controller->SetPressed(btn, true);
	controller->SetHeld(btn, true);
}

void InputManager::HandleKeyReleased(const sf::Event& event)
{
	m_keyHeld[event.key.code] = false;
	m_keyPressed[event.key.code] = false;
	m_keyReleased[event.key.code] = true;
}

void InputManager::HandleJoystickReleased(const sf::Event& event)
{

	unsigned int id = event.joystickButton.joystickId;
	Controller* controller = m_controllerList[id];
	Controller::Button btn = static_cast<Controller::Button>(event.joystickButton.button);

	controller->SetPressed(btn, false);
	controller->SetHeld(btn, false);
	controller->SetReleased(btn, true);
}

void InputManager::HandleJoystickConnection(const sf::Event& event)
{
	unsigned int id = event.joystickButton.joystickId;

	if (m_controllerList.contains(id))
		m_controllerList[id]->Connect();
	else
		m_controllerList[id] = new Controller(id);

	std::string msg = "Controller " + std::to_string(id) + " connected"; 
	Debug::Get()->DebugMessage(Debug::Severity::INFO, "Controller", msg);
}

void InputManager::HandleJoystickDisconnection(const sf::Event& event)
{
	unsigned int id = event.joystickButton.joystickId;

	m_controllerList[id]->Disconnect();

	std::string msg = "Controller " + std::to_string(id) + " disconnected";
	Debug::Get()->DebugMessage(Debug::Severity::WARN, "Controller", msg);
}


InputManager::~InputManager()
{
	for (auto& pair : m_controllerList)
		delete pair.second;

	m_controllerList.clear();
}

void InputManager::Init()
{
	for (unsigned int id = 0; id < sf::Joystick::Count; ++id)
	{
		if (sf::Joystick::isConnected(id))
		{
			m_controllerList[id] = new Controller(id);
			std::string msg = "Controller " + std::to_string(id) + " connected";
			Debug::Get()->DebugMessage(Debug::Severity::INFO, "Controller", msg);
		}
	}
}

void InputManager::HandleInput(const sf::Event& event)
{
	switch (event.type)
	{
	case EventType::MouseButtonPressed:
		HandleMousePressed(event);
//		m_mousePressed[event.mouseButton.button] = true;
		break;

	case EventType::KeyPressed:
		HandleKeyPressed(event);
		break;

	case EventType::JoystickButtonPressed:
		HandleJoystickPressed(event);
		break;

	case EventType::KeyReleased:
		HandleKeyReleased(event);
		break;

	case EventType::JoystickButtonReleased:
		HandleJoystickReleased(event);
		break;

	case EventType::JoystickConnected:
		HandleJoystickConnection(event);
		break;

	case EventType::JoystickDisconnected:
		HandleJoystickDisconnection(event);
		break;
	}

	sf::Joystick::update();
}


bool InputManager::IsKeyPressed(sf::Keyboard::Key _key)
{
	if (!m_keyPressed.contains(_key)) return false;

	bool isPressed = m_keyPressed[_key];

	m_keyPressed[_key] = false;
	return isPressed;
}

bool InputManager::IsMousePressed(sf::Mouse::Button _mouseClick)
{
	bool isPressed = m_mousePressed[_mouseClick];
	m_mousePressed[_mouseClick] = false;

	return m_mousePressed[_mouseClick];
}

bool InputManager::IsMouseHeld(sf::Mouse::Button _mouseClick)
{
	return m_mouseHeld[_mouseClick];
}

bool InputManager::IsMouseReleased(sf::Mouse::Button _mouseClick)
{
	return m_mouseReleased[_mouseClick];
}

bool InputManager::IskeyReleased(sf::Keyboard::Key _key)
{
	if (!m_keyReleased.contains(_key)) return false;

	return m_keyReleased[_key];
}

bool InputManager::IsKeyHeld(sf::Keyboard::Key _key)
{
	if (!m_keyHeld.contains(_key)) return false;
	// a little buggy because held is at true at the same frame as pressed should be at minimum the second nevermind it work i think
	return m_keyHeld[_key];
}

bool InputManager::IsControllerPressed(unsigned int _id, Controller::Button _key)
{
	if (!m_controllerList.contains(_id))
		return false;

	bool isPressed = m_controllerList[_id]->IsControllerPressed(_key);  // Ok so i have no idea why it doesn't work so i just do that this way for now
	m_controllerList[_id]->SetPressed(_key, false);

	return isPressed;
}

bool InputManager::IsControllerReleased(unsigned int _id, Controller::Button _key)
{
	if (!m_controllerList.contains(_id))
		return false;

	return m_controllerList[_id]->IsControllerReleased(_key);
}

bool InputManager::IsControllerHeld(unsigned int _id, Controller::Button _key)
{
	if (!m_controllerList.contains(_id))
		return false;

	return m_controllerList[_id]->IsControllerHeld(_key);
}


float InputManager::GetJoystickLeftX(unsigned int _id)
{
	if (!m_controllerList.contains(_id))
		return 0.0f;

	return m_controllerList[_id]->GetJoystickLeftX();
}

float InputManager::GetJoystickLeftY(unsigned int _id)
{
	if (!m_controllerList.contains(_id))
		return 0.0f;

	return m_controllerList[_id]->GetJoystickLeftY();
}

float InputManager::GetJoystickRightX(unsigned int _id)
{
	if (!m_controllerList.contains(_id))
		return 0.0f;

	return m_controllerList[_id]->GetJoystickRightX();
}

float InputManager::GetJoystickRightY(unsigned int _id)
{
	if (!m_controllerList.contains(_id))
		return 0.0f;

	return m_controllerList[_id]->GetJoystickRightY();
}

float InputManager::GetTriggerLvl(unsigned int _id)
{
	if (!m_controllerList.contains(_id))
		return 0.0f;

	return m_controllerList[_id]->GetTriggerLvl();
}


std::vector<unsigned int> InputManager::GetAvailableController()
{
	if (m_controllerList.empty())
		return {};


	std::vector<unsigned int> availableList;

	for (auto& pair : m_controllerList)
		availableList.push_back(pair.first);

	return availableList;
}

bool InputManager::IsJoysticConnected(int _id)
{
	if (!m_controllerList.contains(_id))
		return false;

	return m_controllerList[_id]->IsConnected();
}

void InputManager::Reset()
{
	//m_keyReleased.clear();
	//m_keyPressed.clear();

	//for (auto& pair : m_controllerList)
	//	pair.second->Reset();
}