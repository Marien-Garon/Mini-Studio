#include "Parallaxe.h"

void Parallaxe::OnInitialize()
{
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));

	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));

	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));

	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));

	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(2545, 720, sf::Color::Green));
}

void Parallaxe::Start()
{
}

void Parallaxe::Stop()
{
}
