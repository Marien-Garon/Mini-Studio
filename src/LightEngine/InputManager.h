#pragma once
#include "Controller.h"

/// <summary>
/// Gestion des inputs autant au clavier qu'a la manettes
/// </summary>
class InputManager
{
private:
	
	std::unordered_map<sf::Keyboard::Key, bool> m_keyPressed;
	std::unordered_map<sf::Keyboard::Key, bool> m_keyHeld;
	std::unordered_map<sf::Keyboard::Key, bool> m_keyReleased;
	std::unordered_map<sf::Mouse::Button, bool> m_mousePressed;

	std::unordered_map<unsigned int, Controller*> m_controllerList;

	void HandleKeyPressed(const sf::Event& event);
	void HandleJoystickPressed(const sf::Event& event);
	void HandleKeyReleased(const sf::Event& event);
	void HandleJoystickReleased(const sf::Event& event);
	void HandleJoystickConnection(const sf::Event& event);
	void HandleJoystickDisconnection(const sf::Event& event);


public:

	static InputManager& Get() {
		static InputManager instance;
		return instance; 
	}

	~InputManager();

	void Init();


	void HandleInput(const sf::Event& event);


	bool IsKeyPressed(sf::Keyboard::Key _key);
	bool IsMousePressed(sf::Mouse::Button _mouseClick);


	bool IskeyReleased(sf::Keyboard::Key _key);
	bool IsKeyHeld(sf::Keyboard::Key _key);


	bool IsControllerPressed(unsigned int _id, Controller::Button _key);
	bool IsControllerReleased(unsigned int _id, Controller::Button _key);
	bool IsControllerHeld(unsigned int _id, Controller::Button _key);


	float GetJoystickLeftX(unsigned int _id);
	float GetJoystickLeftY(unsigned int _id);
	float GetJoystickRightX(unsigned int _id);
	float GetJoystickRightY(unsigned int	 _id);
	float GetTriggerLvl(unsigned int _id);

	std::vector<unsigned int> GetAvailableController();

	bool IsJoysticConnected(int _id);
	void Reset();
};