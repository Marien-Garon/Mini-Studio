#include "Parallaxe.h"
#include "SampleScene.h"
#include "AssetManager.h"
#include "Camera.h"

void Parallaxe::OnInitialize()
{
	AssetManager& AM = AssetManager::getInstance();

	// Background
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("fond"), sf::Color::Green));
	m_backgrounds[0]->SetSpeed(0);
	
	// Layer 1
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer1"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer1"), sf::Color::Green));
	m_backgrounds[1]->SetSpeed(25.f);
	m_backgrounds[2]->SetSpeed(25.f);

	// Layer 2
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer2"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer2"), sf::Color::Green));
	m_backgrounds[3]->SetSpeed(50.f);
	m_backgrounds[4]->SetSpeed(50.f);

	// Layer 3
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer3"), sf::Color::Green));
	m_backgrounds.push_back(CreateEntity<Background>(AM.LoadSprite("layer3"), sf::Color::Green));
	m_backgrounds[5]->SetSpeed(75.f);
	m_backgrounds[6]->SetSpeed(75.f);

	sf::Vector2f cameraPos = GetScene<SampleScene>()->GetCamera()->GetView()->getCenter();
	float windowWidth = GetScene<SampleScene>()->GetWindowWidth();
	for (int i = 0; i < m_backgrounds.size(); i++) {
		if (i == 0) {
			m_backgrounds[i]->SetPosition(cameraPos.x, cameraPos.y);
		}else if (i % 2  != 0) {
			m_backgrounds[i]->SetPosition(cameraPos.x, cameraPos.y);
		}
		else {
			m_backgrounds[i]->SetPosition(cameraPos.x + windowWidth / 2, cameraPos.y, 0.f, 0.5f);
		}
	}
}

void Parallaxe::Start()
{
	for (int i = 0; i < m_backgrounds.size(); i++) {
		m_backgrounds[i]->SetDirection(-1, 0);
	}
}

void Parallaxe::Stop()
{
	for (int i = 0; i < m_backgrounds.size(); i++) {
		m_backgrounds[i]->SetDirection(0, 0);
	}
}
