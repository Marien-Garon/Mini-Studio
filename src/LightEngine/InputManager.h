#pragma once
#include "Controller.h"

/// <summary>
/// Manage input of the controller and the keyboard (not mouse yet)
/// </summary>
class InputManager
{
private:

	std::unordered_map<sf::Keyboard::Key, bool> m_keyPressed;
	std::unordered_map<sf::Keyboard::Key, bool> m_keyHeld;
	std::unordered_map<sf::Keyboard::Key, bool> m_keyReleased;
	std::unordered_map<sf::Mouse::Button, bool> m_mousePressed;
	std::unordered_map<sf::Mouse::Button, bool> m_mouseHeld;
	std::unordered_map<sf::Mouse::Button, bool> m_mouseReleased;

	std::unordered_map<unsigned int, Controller*> m_controllerList;

	void HandleMousePressed(const sf::Event& event);
	void HandleMouseReleased(const sf::Event& event);
	void HandleKeyPressed(const sf::Event& event);
	void HandleJoystickPressed(const sf::Event& event);
	void HandleKeyReleased(const sf::Event& event);
	void HandleJoystickReleased(const sf::Event& event);
	void HandleJoystickConnection(const sf::Event& event);
	void HandleJoystickDisconnection(const sf::Event& event);

	sf::Vector2i m_mousePos;

	sf::Vector2i m_clickPos;


public:

	static InputManager& Get() {
		static InputManager instance;
		return instance;
	}

	~InputManager();

	void Init();

	void HandleInput(const sf::Event& event);


	sf::Vector2i GetMousePos() { return m_mousePos; };
	sf::Vector2i GetMouseClickPos() { return m_clickPos; };

	/// <summary>
	/// Return if a key was pressed
	/// </summary>
	/// <param name="_key -> sf::Keyboard::Key"></param>
	/// <returns> boolean </returns>
	bool IsKeyPressed(sf::Keyboard::Key _key);

	bool IsMousePressed(sf::Mouse::Button _mouseClick);
	bool IsMouseHeld(sf::Mouse::Button _mouseClick);
	bool IsMouseReleased(sf::Mouse::Button _mouseClick);
	/// <summary>
	/// Return if a key was released
	/// </summary>
	/// <param name="_key -> sf::Keyboard::Key"></param>
	/// <returns> boolean </returns>
	bool IskeyReleased(sf::Keyboard::Key _key);

	/// <summary>
	/// Return if a key is held
	/// </summary>
	/// <param name="_key -> sf::Keyboard::Key"></param>
	/// <returns> boolean </returns>
	bool IsKeyHeld(sf::Keyboard::Key _key);

	/// <summary>
	/// Return if a buttton of the controller was pressed
	/// </summary>
	/// <param name="_id -> id of the controller use 0 if you don't know"></param>
	/// <param name="_key -> Controller::Button"></param>
	/// <returns>boolean</returns>
	bool IsControllerPressed(unsigned int _id, Controller::Button _key);

	/// <summary>
	/// Return if a buttton of the controller was released
	/// </summary>
	/// <param name="_id -> id of the controller use 0 if you don't know"></param>
	/// <param name="_key -> Controller::Button"></param>
	/// <returns>boolean</returns>
	bool IsControllerReleased(unsigned int _id, Controller::Button _key);

	/// <summary>
	/// Return if a buttton of the controller is held
	/// </summary>
	/// <param name="_id -> id of the controller use 0 if you don't know"></param>
	/// <param name="_key -> Controller::Button"></param>
	/// <returns>boolean</returns>
	bool IsControllerHeld(unsigned int _id, Controller::Button _key);

	/// <summary>
	/// Return the axis X level of the left joystick
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	float GetJoystickLeftX(unsigned int  _id = 0);

	/// <summary>
	/// Return the axis Y level of the left joystick
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	float GetJoystickLeftY(unsigned int  _id = 0);

	/// <summary>
	/// Return the axis X level of the right joystick
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	float GetJoystickRightX(unsigned int _id = 0);

	/// <summary>
	/// Return the axis Y level of the right joystick
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	float GetJoystickRightY(unsigned int _id = 0);

	/// <summary>
	/// Return the trigger lever of the two trigger L&R
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	float GetTriggerLvl(unsigned int _id = 0);

	/// <summary>
	/// Return a vector of all controller available if none return a vector with a length of 0
	/// </summary>
	/// <returns> vector of unsigned int</returns>
	std::vector<unsigned int> GetAvailableController();

	/// <summary>
	/// Return true if the controller at the id is connected
	/// </summary>
	/// <param name="_id -> id of the controller 0 by default"></param>
	/// <returns>boolean</returns>
	bool IsJoysticConnected(int _id = 0);


	void Reset();
};
